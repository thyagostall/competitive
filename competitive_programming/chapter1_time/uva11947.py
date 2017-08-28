import datetime

def create_date(day, month, year):
    return datetime.date(day=day, month=month, year=year)

def sign(date):
    year = date.year
    if create_date(21, 1, year) <= date <= create_date(19, 2, year):
        return 'aquarius'
    elif create_date(20, 2, year) <= date <= create_date(20, 3, year):
        return 'pisces'
    elif create_date(21, 3, year) <= date <= create_date(20, 4, year):
        return 'aries'
    elif create_date(21, 4, year) <= date <= create_date(21, 5, year):
        return 'taurus'
    elif create_date(22, 5, year) <= date <= create_date(21, 6, year):
        return 'gemini'
    elif create_date(22, 6, year) <= date <= create_date(22, 7, year):
        return 'cancer'
    elif create_date(23, 7, year) <= date <= create_date(21, 8, year):
        return 'leo'
    elif create_date(22, 8, year) <= date <= create_date(23, 9, year):
        return 'virgo'
    elif create_date(24, 9, year) <= date <= create_date(23, 10, year):
        return 'libra'
    elif create_date(24, 10, year) <= date <= create_date(22, 11, year):
        return 'scorpio'
    elif create_date(23, 11, year) <= date <= create_date(22, 12, year):
        return 'sagittarius'
    else:
        return 'capricorn'

def read_test_case_quantity():
    result = input()
    return int(result)

def read_test_case():
    date = input()
    
    month = int(date[:2])
    day   = int(date[2:4])
    year  = int(date[4:])
    return datetime.date(day=day, month=month, year=year)

def compute(date):
    date = date + datetime.timedelta(days=40*7)
    return date, sign(date)

def main():
    test_case_quantity = read_test_case_quantity()
    for test_case_number in range(1, test_case_quantity + 1):
        test_case = read_test_case()
        date, sign = compute(test_case)
        print(test_case_number, date.strftime("%m/%d/%Y"), sign)
        test_case_quantity -= 1

if __name__ == '__main__':
    main()
