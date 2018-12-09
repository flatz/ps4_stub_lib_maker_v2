#!/usr/bin/env python2.7

import sys, os, re

if len(sys.argv) < 2:
	script_file_name = os.path.split(sys.argv[0])[1]
	print('usage: {0} <header file>'.format(script_file_name))
	sys.exit()

hdr_file_path = sys.argv[1]
if not os.path.isfile(hdr_file_path):
	print('error: invalid header file specified')
	sys.exit(1)

cond_start_regexp = re.compile(r'^\s*#\s*(if|ifdef|ifndef)\s+')
cond_end_regexp = re.compile(r'^\s*#\s*endif\s*$')
prototypes_start_regexp = re.compile(r'^\s*#\s*(if|ifdef)\s+([A-Za-z0-9_]+)_PROTOTYPES\s*$')
version_start_regexp = re.compile(r'^\s*#\s*(if|ifdef|ifndef)\s+EGL_VERSION_([A-Za-z0-9_]+)\s*$')
api_call_regexp = re.compile(r'^\s*((GL_APICALL|EGLAPI)\s+.+?);\s*$')

with open(hdr_file_path, 'rb') as f:
	cond_count = 0
	marked_depth = -1
	prototype_line_num = -1

	for i, line in enumerate(f.readlines()):
		line = line.rstrip('\r\n').strip()
		if len(line) == 0:
			continue

		if cond_start_regexp.match(line):
			cond_count += 1
			if prototypes_start_regexp.match(line) or version_start_regexp.match(line):
				marked_depth = cond_count
				prototype_line_num = i + 1
		elif cond_end_regexp.match(line):
			if marked_depth == cond_count:
				marked_depth = -1
				prototype_line_num = -1
			cond_count -= 1

		if marked_depth >= 0 and i >= prototype_line_num:
			matches = api_call_regexp.match(line)
			if matches:
				line = matches.group(1)
				pos = line.find('(')
				if pos > 0:
					words = line[:pos].split()
					name = words[-1]
					print(name)
