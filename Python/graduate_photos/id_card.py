import calendar

__CNO__ = [1, 0, 10, 9, 8, 7, 6, 5, 4, 3, 2]
__W__ = [7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2]


with open('district_code_only.txt') as f:
    DISTRICT_CODES = f.readlines()
DISTRICT_CODES = [[int(c) for c in code.strip()] for code in DISTRICT_CODES]


def validate(id_no):
    assert len(id_no) == 18
    if id_no[17] == 'X' or id_no[17] == 'x':
        id_no[17] = 10
    Y = sum([a * __W__[w] for w, a in enumerate(id_no[:17])]) % 11
    return Y == __CNO__[id_no[17]]


def valid_code(id_no):
    return __CNO__[sum([a * __W__[w] for w, a in enumerate(id_no[:17])]) % 11]


def enum_date_codes(since=1990, to_ex=2000):
    for year in range(since, to_ex):
        year_digits = [int(c) for c in '%04d' % year]
        isleap = calendar.isleap(year)
        for month in range(1, 13):
            month_digits = [int(c) for c in '%02d' % month]
            for day in range(1, calendar.monthrange(year, month)[1] + 1):
                day_digits = [int(c) for c in '%02d' % day]
                date_code = year_digits + month_digits + day_digits
                assert len(date_code) == 8
                yield date_code


def enum_order_codes():
    for a in range(10):
        for b in range(10):
            for c in range(10):
                yield [a, b, c]


def enum_all_possible(since=1990, to_ex=2000):
    date_codes = list(enum_date_codes(since, to_ex))
    order_codes = list(enum_order_codes())
    for dist_code in DISTRICT_CODES:
        for date_code in date_codes:
            for order_code in order_codes:
                id_no = dist_code + date_code + order_code
                id_no.append(valid_code(id_no))
                yield to_str(id_no)


def to_str(id_no, x_as='X'):
    if id_no[17] == 10:
        id_no[17] = x_as
    id_no = [str(i) for i in id_no]
    return ''.join(id_no)
