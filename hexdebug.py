def string_chunks(string, x):
    new = ''
    cnt = 0
    i = 0
    for ch in string:
        if cnt%x==0 and cnt!=0: # checking if cnt is a multiple of x and not 0, we don't want to put star at index 0
            new += f':{str(int((i / 2) - 1))} '
        cnt += 1
        new += ch
        i = i + 1
    return new
print(string_chunks("81823bf6332c4cfcfc4c2c33332c4cfc", 2))