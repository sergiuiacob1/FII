def validate_dict(rules, dic):
    for key in dic:
        rulesForKey = [rule for rule in rules if rule[0] == key]
        if len(rulesForKey) == 0:
            print(f'{key} appears in the dictionary but there are no rules for it!')
            return False
        for rule in rulesForKey:
            if (dic[key].startswith(rule[1]) == False) or ((rule[2] in dic[key]) == False) or (dic[key].endswith(rule[3]) == False):
                print(
                    f'"{key}": "{dic[key]}" does not respect this rule: {rule}')
                return False

    return True


print(validate_dict([("key1", "", "inside", ""), ("key2", "start", "middle", "winter")], {
      "key2": "starting the engine in the middle of the winter", "key1": "come inside, it's too cold outside"}))
