go = ''
class funcs:
    def echo(x):
        print(x)
    def ask(x):
        return input(x)
def parse(code):
    for i in code:
        if i[0] == "function":
            globals()["go"] = i[1]
        elif i[0]=="string":
            eval(f"funcs.{go}('{i[1]}')")
