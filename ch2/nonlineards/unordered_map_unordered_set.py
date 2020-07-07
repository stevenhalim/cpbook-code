def main():
    mapper = dict()
    used_values = {-1} # initialize with dummy value

    # suppose we enter these 7 name-score pairs below
    # john 78
    # billy 69
    # andy 80
    # steven 77
    # felix 82
    # grace 75
    # martin 81

    mapper["john"] = 78
    used_values.add(78)
    mapper["billy"] = 69
    used_values.add(69)
    mapper["andy"] = 80
    used_values.add(80)
    mapper["steven"] = 77
    used_values.add(77)
    mapper["felix"] = 82
    used_values.add(82)
    mapper["grace"] = 75
    used_values.add(75)
    mapper["martin"] = 81
    used_values.add(81)

    # then the internal content of mapper/used_values are not really known
    # (implementation dependent)

    # iterating through the content of mapper may give any order (input order or jumbled order)
    # as the keys are hashed into various slots
    for key, value in mapper.items():
        print("{} {}".format(key, value))

    # map can also be used like this
    print("steven's score is {}, grace's score is {}".format(mapper["steven"], mapper["grace"]))
    print("==================")

    # there is no lower_bound and upper_bound in a Python set

    # O(1) search, found
    print("{}".format(77 in used_values))
    # O(1) search, not found
    if not 79 in used_values:
        print("79 not found")

main()
