package rerouter

import (
	"net/http"
	"net/url"
	"regexp"
)

type router struct {
	regex   *regexp.Regexp
	params  []string
	handler http.HandlerFunc
}

type RERouteMux struct {
	routers []*router
}

// Initialize an empty RERouteMux
func New() *RERouteMux {
	return &RERouteMux{}
}

// Register a new route and add it into multiplexer. 
// The `pattern` string can contain parameters and 
// regular expressions (optional). 
// Parameters should be put into a pair of curly brackets. 
// Regular expressions should be put into a pair of round brackets. 
func (mux *RERouteMux) Register(pattern string, handler http.HandlerFunc) (err error) {

	// valid regular expression of parameters
	// IMPOSSIBLE TO PANIC
	param := regexp.MustCompile("{[a-zA-Z][0-9a-zA-Z]*}")

	// default regular expression for the parameters which are not
	// specified with any regular expression
	replacement := "([a-zA-Z][0-9a-zA-Z]*)"

	// find all parameters
	params := param.FindAllString(pattern, -1)

	// delete parameters which are specified with regular expression
	// IMPOSSIBLE TO PANIC
	del := regexp.MustCompile("{[a-zA-Z][0-9a-zA-Z]*}\\([^/]+\\)")
	raw := del.ReplaceAllStringFunc(pattern, reserveRegex)

	// get the regular expression of the entire pattern
	re := param.ReplaceAllString(raw, replacement)
	regex, err := regexp.Compile(re)
	if err != nil {
		return
	}

	// create new router
	route := new(router)
	route.regex = regex
	for _, p := range params {
		route.params = append(route.params, p[1:len(p)-1])
	}
	route.handler = handler

	// append the new router to the list in the multiplexer
	mux.routers = append(mux.routers, route)

	return
}

// Required by http.Handler interface. This method is invoked by the
// http server and will handle all page routing
func (mux *RERouteMux) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	requestPath := r.URL.Path

	for _, router := range mux.routers {
		// if this router does not match the url, then continue
		if !router.regex.MatchString(requestPath) {
			continue
		}

		// get submatches: the 1st is the entire url, others are 
		// parameters
		submatches := router.regex.FindStringSubmatch(requestPath)
		// just check the length to get better efficiency
		if len(submatches[0]) != len(requestPath) {
			continue
		}

		// encode the parameters into r.URL.RawQuery 
		if len(router.params) > 0 {
			values := r.URL.Query()
			for i, match := range submatches[1:] {
				values.Add(router.params[i], match)
			}

			r.URL.RawQuery = url.Values(values).Encode() + "&" + r.URL.RawQuery
		}

		router.handler(w, r)
		return
	}

	http.NotFound(w, r)
}

func reserveRegex(pattern string) (replacement string) {
	// if `pattern` string is not the specified format, 
	// then do not change anything, just return the input string
	// IMPOSSIBLE TO PANIC
	check := regexp.MustCompile("{[a-zA-Z][0-9a-zA-Z]*}\\([^/]+\\)")
	if !check.MatchString(pattern) {
		return pattern
	}

	// IMPOSSIBLE TO PANIC
	repl := regexp.MustCompile("\\([^/]+\\)")
	return repl.FindString(pattern)
}
