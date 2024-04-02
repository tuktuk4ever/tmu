#!/usr/bin/env python3
import os
import subprocess

# execute './switchconf.sh --list' to get the list of available configurations
output = subprocess.check_output(['bash', './switchconf.sh', '--list']).decode('utf-8').splitlines()

if not os.path.exists('./sdkconfig'):
    print('Please execute "./switchconf.sh <config>" for initial file creation')
    exit(1)

# read symlink './sdkconfig' to get the current configuration
current_config = os.readlink('./sdkconfig').split('sdkconfig_')[1]

if len(output) == 0:
    print('No configurations found!')
    exit(1)

# check if PATH (env) contains 'bobbycar-boardcomputer-firmware
if not os.environ['IDF_PATH']:
    print('Please execute ". export.sh"')
    exit(1)

for config in output:
    print('Switching to configuration: ' + config)
    subprocess.check_call(['bash', './switchconf.sh', config])
    # execute idf.py menuconfig and wait for user to close again
    subprocess.check_call(['idf.py', 'menuconfig'])

# switch back to current configuration
print('Switching back to configuration: ' + current_config)
subprocess.check_call(['bash', './switchconf.sh', current_config])
