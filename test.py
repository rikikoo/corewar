#! /usr/bin/env python3

import sys

g_latest_cycle = {}

def sti_comp(a, b):
	a_expr = a.split(' to')[1].split()
	b_expr = b.split(':')[1].split()
	return int(a_expr[0].lstrip('-')) % 512 == int(b_expr[0].lstrip('-')) \
		and int(a_expr[2].lstrip('-')) % 512 == int(b_expr[2].lstrip('-')) \
		and int(a_expr[4].lstrip('-')) % 512 == int(b_expr[4].lstrip('-'))

def ldi_comp(a, b):
	a_expr = a.split('from')[1].split()
	b_expr = b.split(':')[1].split()
	return int(a_expr[0].lstrip('-')) % 512 == int(b_expr[0].lstrip('-')) \
		and int(a_expr[2].lstrip('-')) % 512 == int(b_expr[2].lstrip('-')) \
		and int(a_expr[4].lstrip('-')) % 512 == int(b_expr[4].lstrip('-'))

def op_compare(a, b):
	if a[0] == "live":
		return b[0] == "live" and a[1] == b[1]

	if "ld" in a[0]:
		if a[0] != b[0]:
			return False
		return a[1] == b[1] and a[2] in b[2]

	if a[0] == "st":
		if b[0] != "st":
			return False
		return a[1] in b[1] and a[2] == b[2]

	if a[0] == "add":
		if b[0] != "add":
			return False
		return a[1] in b[1] and a[2] in b[2] and a[3] in b[3]

	if a[0] == "sub":
		if b[0] != "sub":
			return False
		return a[1] in b[1] and a[2] in b[2] and a[3] in b[3]

	if a[0] == "and":
		if b[0] != "and":
			return False
		return a[1] in b[1] and a[2] in b[2] and a[3] in b[3]

	if a[0] == "or":
		if b[0] != "or":
			return False
		return a[1] in b[1] and a[2] in b[2] and a[3] in b[3]

	if a[0] == "xor":
		if b[0] != "xor":
			return False
		return a[1] in b[1] and a[2] in b[2] and a[3] in b[3]

	if a[0] == "zjmp" and ' '.join(a) != ' '.join(b):
		return False

	if "ldi" in a[0]:
		if "ldi" not in b[0]:
			return False
		if a[1].lstrip('-').isdigit() and a[1] != b[1]:
			return False
		else:
			if a[1] not in b[1]:
				return False
		if a[2].lstrip('-').isdigit() and a[2] != b[2]:
			return False
		else:
			if a[2] not in b[2]:
				return False
		return a[3] in b[3]

	if a[0] == "sti":
		if b[0] != "sti":
			return False
		if a[1] not in b[1]:
			return False
		if a[2].lstrip('-').isdigit() and a[2] not in b[2]:
			return False
		else:
			if a[2] not in b[2]:
				return False
		if a[3].lstrip('-').isdigit() and a[3] not in b[3]:
			return False
		else:
			if a[3] not in b[3]:
				return False

	if "fork" in a[0]:
		if a[0] != b[0]:
			return False
		if a[0] == "fork":
			return int(a[1].lstrip('-')) % 512 == int(b[1].lstrip('-'))
		else:
			return a[1] == b[1]

	return True


def compare(a, b):
	if "It is" in a:
		a_n = a.split()[-1]
		b_n = b.split()[-1]
		g_latest_cycle['orig latest cycle'] = a_n
		g_latest_cycle['test latest cycle'] = b_n
		if a_n != b_n:
			return False
		return True

	elif a[0] == 'P':
		if "Process" in b:
			a_elems = a.split()
			a_pc = a_elems[1]
			a_op = a_elems[3]
			b_elems = b.split()
			b_pc = b_elems[1]
			b_op = b_elems[3]
		else:
			return False
		if a_pc != b_pc or a_op != b_op:
			return False
		return op_compare(a_elems[3:], b_elems[3:])

	elif "to die" in a:
		return a in b

	elif "store to" in a:
		return sti_comp(a, b)

	elif "load from" in a:
		return ldi_comp(a, b)

	elif "has won" in a:
		if "has won" not in b:
			return False
		if a.split()[1][0] != b.split()[1]:
			return False
		return True

	return False


def parse_outputs(orig, test):
	a = orig
	b = test
	for i, line in enumerate(orig):
		if "It is" in line:
			a = orig[i:]
			break
	for i, line in enumerate(test):
		if "Cycle" in line:
			b = test[i:]
			break

	a_len = len(a)
	b_len = len(b)
	i = 0
	while i < a_len and i < b_len:
		same = compare(a[i], b[i])
		if not same:
			print(f"different values on line {i}!")
			print(f"{g_latest_cycle}\n")
			print(f">>> {a[i]}")
			print("----------")
			print(f"<<< {b[i]}")
			ans = input("\n\nContinue? (y/n) ")
			if ans != 'y':
				break
		i += 1


def main():
	if len(sys.argv) != 3:
		print(f"usage: {sys.argv[0]} <orig_corewar_output> <test_corewar_output>\n")
		print("run original corewar with cycle and operation verbosity, like so:")
		print("\t./corewar -v 6 <champ1> <champ2> <...>\n")
		print("and of course the test corewar with the same verbosity and champ order")
		print("\t./corewar -v 3 <c1> <c2> <...>\t\t<--- rkyttala's corewar example")
		quit()

	orig_file = sys.argv[1]
	test_file = sys.argv[2]

	try:
		with open(orig_file, 'r') as f1:
			orig = [line.strip() for line in f1 if line != "\n"]
	except FileNotFoundError:
		print(f"Error: couldn't open file '{orig_file}'")
		quit()
	try:
		with open(test_file, 'r') as f2:
			test = [line.strip() for line in f2 if line != "\n"]
	except FileNotFoundError:
		print(f"Error: couldn't open file '{test_file}'")
		quit()

	if len(orig) != len(test):
		print("Line counts of outputs do not match!")
		ans = input("continue anyway? (y/n) ")
		if ans.lower() != 'y':
			print("quitting")
			quit()

	parse_outputs(orig, test)
	print("\nTest completed. If there was no output before this, 'sall good man!")


if __name__ == "__main__":
	main()
