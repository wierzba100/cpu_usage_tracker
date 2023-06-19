import time
import subprocess


def sigterm_test():
    cpu_usage_app = subprocess.Popen("./cpu_usage_tracker", stdout=subprocess.PIPE)

    time.sleep(3)

    cpu_usage_app.terminate()

    cpu_usage_app.wait()

    out = cpu_usage_app.stdout.read()
    string_out = str(out)

    if string_out[-17:] == "Program closed\\n'":
        return 1
    else:
        return 0


assert sigterm_test() == 1

