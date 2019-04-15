// Copyright 2012-2013 leon-huang. All rights reserved.
// Use of this source code is governed by GPL v3
// license that can be found in the official website of GNU.

/*
Package rerouter provides An simple RESTful HTTP router 
for Go.It allows users to register parameters and 
supports regular expression.

Create a new route multiplexer:

	mux := rerouter.New()

Register a simple route with a path and http.HandleFunc:

	mux.Register("/foo", fooHandler)

Register a route with restful parameters followed by a regular 
expressions (optional) in the path:

	mux.Register("/{userid}([0-9]+)\\+{username}", 
			func(w http.ResponseWriter, r *http.Request) {
		params := r.URL.Query()
		userid := params.Get("userid")
		username := params.Get("username")
		fmt.Fprintf(w, "%s %s", userid, username)
	})

The parameters are parsed from the URL, and appended to the Request URL's
query parameters.

There is a few things you should NOTE:

	a) Regular expressions can only follow the parameters and describes
	the parameters. One parameter has at most one regular expression.
	b) The standard for regular expression is the same with what Go 
	programming language supports.
	c) A valid parameter is a sequence of one or more letters and 
	digits. The first character in an identifier must be a letter.
	d) There should only be one parameter between two adjacent "/"s, 
	although it is not forced to be, or you'll get mysterious things.
	e) Remember all the time: you are playing with a regular expression, 
	that is, don't forget escaping characters when you don't want them 
	to be regular


To start the web server, use the standard http.ListenAndServe
function, and provide the route multiplexer:

	err := http.ListenAndServe(":8080", mux)
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}
*/
package rerouter
