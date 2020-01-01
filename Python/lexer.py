import parse

code = "echo 'Hello, World!'"
tokens = {
    "function": [
        "echo",
        "ask"
    ],
    "id": [
        "'"
    ]
}

found = []
for k,v in tokens.items():
    for i in v:
        if k == "function":
            mention = code.find(i)
            if mention != -1:
                found.append((k, i))
        if k == "id":
            mention = code.find(i)
            altered_code = list(code)
            del altered_code[mention]
            altered_code = ''.join(altered_code)
            mention2 = altered_code.find(i)
            found.append(("string", code[mention+1:mention2+1]))


parse.parse(found)
