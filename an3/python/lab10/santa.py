import datetime

now = datetime.datetime.now()
Christmas = datetime.datetime(2019, 12, 25, 3, 33, 33)
print(
    f'There are {(Christmas - now).total_seconds()} seconds until Christmas!!!')
