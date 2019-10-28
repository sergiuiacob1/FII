lambdas = {
    "print_all": lambda *a, **k: print(a, k),
    "print_args_commas": lambda *a, **k: print(a, k, sep=", "),
    "print_only_args": lambda *a, **k: print(a),
    "print_only_kwargs": lambda *a, **k: print(k)
}


def apply_function(command, *a, **k):
    return lambdas[command](*a, **k)


apply_function("print_args_commas", 1, 2, 3, href='test', altcv='alt test')
