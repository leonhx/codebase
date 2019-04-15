"""
A class that can store key-value pairs.
"""

class KeyValue():
    """Store key-value pairs, of which the key is a string.

    **NOTE** The key cannot start with an underline.

    For example:
    >>> kv = KeyValue(foo=12, bar="hello", baz=lambda x : x % 2 == 0)
    >>> kv.foo
    12
    >>> kv.bar
    "hello"
    >>> kv.baz(12)
    True
    """
    def __init__(self, **kwargs):
        self.__kwargs__ = kwargs
        for k in kwargs:
            if k.startswith('_'):
                raise AttributeError('keyword cannot start with underline')
            setattr(self, k, kwargs[k])
    def __unicode__(self):
        pairs = ['%s=%s' % (unicode(k), unicode(self.__kwargs__[k]))
                 for k in self.__kwargs__]
        return u'%s(%s)' % (self.__class__.__name__, ', '.join(pairs))
    def __str__(self):
        pairs = ['%s=%s' % (str(k), str(self.__kwargs__[k]))
                 for k in self.__kwargs__]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(pairs))
    def __repr__(self):
        pairs = ['%s=%s' % (str(k), repr(self.__kwargs__[k]))
                 for k in self.__kwargs__]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(pairs))
    def __eq__(self, that):
        if that is None:
            return False
        if not isinstance(that, self.__class__):
            return False
        try:
            for k in self.__kwargs__:
                if self.__kwargs__[k] != that.__kwargs__[k]:
                    return False
            for k in that.__kwargs__:
                if that.__kwargs__[k] != self.__kwargs__[k]:
                    return False
        except (AttributeError, TypeError):
            return False
        return True
    def __ne__(self, other):
        return not self == other
