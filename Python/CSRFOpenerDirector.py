"""
An OpenerDirector which can handle with anti-CSRF websites.
"""


import urllib2
import socket
import cookielib


class CSRFOpenerDirector(object):

    def __init__(self):
        self.__cookie__ = cookielib.CookieJar()
        cjhdr = urllib2.HTTPCookieProcessor(self.__cookie__)
        self.__opener__ = urllib2.build_opener(cjhdr)

    def __unicode__(self):
        return """Cookie: %s,
Additional Headers: %s
Opener: %s,
""" % (self.__cookie__, self.__opener__.addheaders, self.__opener__)

    def open(self, fullurl, data=None, timeout=socket._GLOBAL_DEFAULT_TIMEOUT):
        csrftoken = None
        for cookie in self.__cookie__:
            if cookie.name == 'csrftoken':
                csrftoken = cookie.value
        if csrftoken:
            self.__opener__.addheaders.append(("X-CSRFToken", csrftoken))
        return self.__opener__.open(fullurl, data, timeout)
