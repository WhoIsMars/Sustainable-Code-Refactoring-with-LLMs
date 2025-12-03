def handle_error_by_throwing_exception():
    raise ValueError('Oops')


def handle_error_by_returning_none(input_data):
    try:
        return int(input_data)
    except ValueError:
        return None


def handle_error_by_returning_tuple(input_data):
    try:
        result = int(input_data)
        return (True, result)
    except ValueError:
        return (False, None)


def filelike_objects_are_closed_on_exception(filelike_object):
    try:
        with filelike_object as f:
            f.do_something()
    except Exception:
        pass