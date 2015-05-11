import time;
while True:
    with open('hello.txt', 'r') as infile:
        for line in infile:
            print(line, end='')
            time.sleep(1)
