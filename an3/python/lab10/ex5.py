import sys
import datetime
from dateutil.relativedelta import relativedelta


no_days = int(sys.argv[1])
original = datetime.datetime(datetime.datetime.now().year, 1, 1, 0, 0, 0)
print(original.strftime("%A"))

for _ in range(0, no_days):
    original -= relativedelta(years=1)
    print(original.strftime("%A"))
