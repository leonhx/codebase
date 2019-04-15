import http.cookiejar
import re
import urllib


def enum_all_possible(start=111250001, end_ex=111250280):
    for i in range(start, end_ex):
        yield str(i)


def valid_student_id(sid):
    cookie = http.cookiejar.CookieJar()
cjhdr  = urllib.request.HTTPCookieProcessor(cookie)
opener = urllib.request.build_opener(cjhdr)

base_url = "http://jwas3.nju.edu.cn:8080/jiaowu/"
login_url = base_url + "login.do"
postdata = urllib.parse.urlencode({'userName': '学号', 'password': '密码'})
postdata = postdata.encode('utf-8')

req = opener.open(login_url, postdata)
print(req.status, req.reason, cookie)

if req.status != 200:
    exit()

gulou_campus = urllib.parse.quote("鼓楼校区")
xianlin_campus = urllib.parse.quote("仙林校区")
course_url = base_url + "student/elective/courseList.do"
gulou_url = course_url + "?method=discussRenewCourseList&campus="+gulou_campus
xianlin_url = course_url + "?method=discussRenewCourseList&campus="+xianlin_campus

while True:
    f = opener.open(xianlin_url).read().decode('utf8')
    courseIDs = re.findall(regex, f)

    for cid in courseIDs:
        select_url = course_url + "?method=submitDiscussRenew&classId="+cid+"&campus="+xianlin_campus
        req = opener.open(select_url)
        print("CourseId:", cid, ", Status:", req.status, req.reason)

    f = opener.open(gulou_url).read().decode('utf8')
    courseIDs = re.findall(regex, f)

    for cid in courseIDs:
        select_url = course_url + "?method=submitDiscussRenew&classId="+cid+"&campus="+gulou_campus
        req = opener.open(select_url)
        print("CourseId:", cid, ", Status:", req.status, req.reason)

