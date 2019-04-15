"""
A class that can store key-value pairs.
"""


class KeyValue():
    """Store key-value pairs, of which the key is a string.

    **NOTE** The key cannot start with an underline unless it is
    '__name__' which has special meaning (type of the object).

    For example:
    >>> kv = KeyValue(__name__='Hello', foo=12, bar="hello",
    ...     baz=lambda x : x % 2 == 0)
    Hello(bar='hello', foo=12, baz=<function <lambda> at 0x2D4665B0>)
    >>> kv.foo
    12
    >>> kv.bar
    "hello"
    >>> kv.baz(12)
    True
    """
    def __init__(self, **kwargs):
        self.__kwargs__ = {k: kwargs[k] for k in kwargs
                           if not k.startswith('_')}
        self.__name__ = self.__class__.__name__
        for k in kwargs:
            if k.startswith('_') and k != '__name__':
                raise AttributeError(
                    'normal keyword cannot start with underline')
            setattr(self, k, kwargs[k])

    def __unicode__(self):
        pairs = ['%s=%s' % (unicode(k), unicode(self.__kwargs__[k]))
                 for k in self.__kwargs__]
        return u'%s(%s)' % (self.__name__, ', '.join(pairs))

    def __str__(self):
        pairs = ['%s=%s' % (str(k), str(self.__kwargs__[k]))
                 for k in self.__kwargs__]
        return '%s(%s)' % (self.__name__, ', '.join(pairs))

    def __repr__(self):
        pairs = ['%s=%s' % (str(k), repr(self.__kwargs__[k]))
                 for k in self.__kwargs__]
        return '%s(%s)' % (self.__name__, ', '.join(pairs))

    def __eq__(self, that):
        this = self
        if that is None or not isinstance(that, this.__class__) or \
                that.__name__ != this.__name__:
            return False
        try:
            for k in this.__kwargs__:
                if this.__kwargs__[k] != that.__kwargs__[k]:
                    return False
            for k in that.__kwargs__:
                if that.__kwargs__[k] != this.__kwargs__[k]:
                    return False
        except (AttributeError, TypeError):
            return False
        return True

    def __ne__(self, other):
        return not self == other
