"""
Utilities about Python networking.
"""


def retry(exceptions, extra_cond=None, delay=None):
    """Retry if encountered `exceptions`.

    extra_cond: A function accepts exception and retry count as parameters.
                It returns whether it is reasonable to retry
    delay: A function accepts exception and retry count as parameters.
           It returns time to sleep before next retry, time unit: second.

    >>> @retry((urllib2.HTTPError, socket.error),
    ...        lambda e, i: e.getcode() == 500 and i < 10,
    ...        lambda e, i: i**3)
    ... def __fetch__(begin, end, conf, query, offset):
    ...     query = urllib.urlencode({
    ...     'APIVersion': '0.2.0',
    ...     'Project': conf.SLS['Project'],
    ...     'Category': conf.SLS['Category'],
    ...     'Topic': '', # Leave empty intendedly
    ...     'BeginTime': __epoch_time__(begin),
    ...     'EndTime': __epoch_time__(end),
    ...     'Query': query,
    ...     'Lines': 200,
    ...     'Offset': offset,
    ... })
    ...
    ... response = urllib2.urlopen('%s?%s' % (__SLS_GETDATA__, query))
    ... page = response.read()
    ... return page
    """
    import time
    if not delay:
        delay = lambda err, i: 0

    def __safe__(func):
        def __bar__(*args, **kwargs):
            i = 0
            while True:
                try:
                    return func(*args, **kwargs)
                except exceptions as err:
                    if extra_cond and not extra_cond(err, i):
                        raise
                    i += 1
                    time.sleep(delay(err, i))
        return __bar__
    return __safe__
