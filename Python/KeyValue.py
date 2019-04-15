"""
A class that can store key-value pairs.
"""


class KeyValue(object):
    """Store key-value pairs, of which the key is a string.

    **NOTE** The key cannot start with an underline unless it is
    '__name__' which has special meaning (type of the object).

    For example:
    >>> kv = KeyValue(__name__='Hello', foo=12, bar="hello",
    ...     baz=lambda x : x % 2 == 0)
    >>> kv.foo
    12
    >>> kv.bar
    'hello'
    >>> kv.baz(12)
    True
    >>> kv == kv
    True
    >>> kv2 = KeyValue(__name__='Hello', foo=12, bar="hello")
    >>> kv2
    Hello(foo=12, bar='hello')
    >>> kv == kv2
    False
    >>> KeyValue(__name__='Hello', foo=12, bar="hello") == kv2
    True
    >>> kv2 == KeyValue(__name__='Hello', foo=11, bar="hello")
    False
    >>> kv2 == KeyValue(__name__='Hi', foo=12, bar="hello")
    False
    """
    def __init__(self, **kwargs):
        for k in kwargs:
            if k.startswith('_') and k != '__name__':
                raise AttributeError(
                    'normal keyword cannot start with underline')
            else:
                self.__dict__[k] = kwargs[k]
        if '__name__' not in kwargs:
            self.__dict__[__name__] = self.__class__.__name__

    def __getattr__(self, name):
        if name in self.__dict__:
            return self.__dict__[name]
        else:
            raise AttributeError(
                '%s has no attribute "%s"' % (self.__name__, name))

    def __setattr__(self, name, value):
        raise AttributeError('%s is immutable' % self.__name__)

    def __delattr__(self, name):
        raise AttributeError('%s is immutable' % self.__name__)

    def __unicode__(self):
        pairs = ['%s=%s' % (unicode(k), unicode(self.__dict__[k]))
                 for k in self.__dict__ if not k.startswith('_')]
        return u'%s(%s)' % (self.__name__, ', '.join(pairs))

    def __str__(self):
        pairs = ['%s=%s' % (str(k), str(self.__dict__[k]))
                 for k in self.__dict__ if not k.startswith('_')]
        return '%s(%s)' % (self.__name__, ', '.join(pairs))

    def __repr__(self):
        pairs = ['%s=%s' % (str(k), repr(self.__dict__[k]))
                 for k in self.__dict__ if not k.startswith('_')]
        return '%s(%s)' % (self.__name__, ', '.join(pairs))

    def __eq__(self, that):
        this = self
        if that is None or not isinstance(that, this.__class__) or \
                that.__name__ != this.__name__:
            return False
        try:
            for k in this.__dict__:
                if this.__dict__[k] != that.__dict__[k]:
                    return False
            for k in that.__dict__:
                if that.__dict__[k] != this.__dict__[k]:
                    return False
        except KeyError:
            return False
        return True

    def __ne__(self, other):
        return not self == other
