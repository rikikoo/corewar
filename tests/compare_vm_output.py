#! /usr/bin/env python3

from re import S
import sys
import os
import subprocess as sp


g_latest_cycle = {}

def sti_comp(a, b):
	if "store to" not in b:
		return False
	a_expr = a.split(' to')[1].split()
	b_expr = b.split(':')[1].split()
	return int(a_expr[2].lstrip('-')) % 512 == int(b_expr[2].lstrip('-')) \
		and int(a_expr[4].lstrip('-')) % 512 == int(b_expr[4].lstrip('-'))

def ldi_comp(a, b):
	if "load from" not in b:
		return False
	a_expr = a.split('from')[1].split()
	b_expr = b.split(':')[1].split()
	return int(a_expr[0].lstrip('-')) % 512 == int(b_expr[0].lstrip('-')) \
		and int(a_expr[2].lstrip('-')) % 512 == int(b_expr[2].lstrip('-'))

def op_compare(a, b):
	if a[0] == "live":
		return b[0] == "live" and a[1] == b[1]

	if a[0] == "ld" or a[0] == "lld":
		if a[0] != b[0]:
			return False
		return a[1] == b[1] and a[2] in b[2]

	if a[0] == "st":
		if b[0] != "st":
			return False
		val = b[2].lstrip('-')
		reg = ''
		if not b[2].lstrip('-').isnumeric():
			reg = b[2].split(':')[0][1:]
		return a[1] in b[1] and \
			(str(int(a[2].lstrip('-')) % 512) == val or a[2] == reg)

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
		if a[1].lstrip('-').isdigit():
			tmp = b[1].split(':')
			if len(tmp) == 2:
				tmp[1] = str(int(tmp[1].lstrip('-')) % 512)
				b[1] = ':'.join(tmp)
			if str(int(a[1].lstrip('-')) % 512) not in b[1]:
				return False
		else:
			if a[1] not in b[1]:
				return False
		if a[2].lstrip('-').isdigit():
			tmp = b[2].split(':')
			if len(tmp) == 2:
				tmp[1] = str(int(tmp[1].lstrip('-')) % 512)
				b[2] = ':'.join(tmp)
			if str(int(a[2].lstrip('-')) % 512) not in b[2]:
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
		if a[2].lstrip('-').isdigit():
			tmp = b[2].split(':')
			if len(tmp) == 2:
				tmp[1] = str(int(tmp[1].lstrip('-')) % 512)
				b[2] = ':'.join(tmp)
			if str(int(a[2].lstrip('-')) % 512) not in b[2]:
				return False
		else:
			if a[2] not in b[2]:
				return False
		if a[3].lstrip('-').isdigit():
			tmp = b[3].split(':')
			if len(tmp) == 2:
				tmp[1] = str(int(tmp[1].lstrip('-')) % 512)
				b[3] = ':'.join(tmp)
			if str(int(a[3].lstrip('-')) % 512) not in b[3]:
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
	ret = False
	while i < a_len and i < b_len:
		if len(a[i]) == 0 or len(b[i]) == 0:
			break
		same = compare(a[i], b[i])
		if not same:
			if not ret:
				ret = True
			print(f"different values on line {i}!")
			print(f"{g_latest_cycle}\n")
			print(f">>> {a[i]}")
			print("----------")
			print(f"<<< {b[i]}")
			ans = input("\n\nContinue? (y/n) ")
			if ans == 'n':
				break
		i += 1
	return ret

def run_corewars():
	# try:
	# 	champ_dir = input("Directory of champs (relative to this prog's path):\n")
	# 	dir_ls = os.listdir(champ_dir)
	# 	champs = []
	# 	for file in dir_ls:
	# 		champ, ext = os.path.splitext('/'.join([champ_dir, file]))
	# 		if ext == ".cor":
	# 			champs.append(champ.split('/')[-1])
	# except EOFError:
	# 	print("Suit yourself")
	# 	quit()
	# except OSError:
	# 	print("Error when getting .cor files.")
	# 	quit()

	champ_dir = "../resources/champs"
	dir_ls = os.listdir(champ_dir)
	champs = []
	for file in dir_ls:
		champ, ext = os.path.splitext('/'.join([champ_dir, file]))
		if ext == ".cor":
			champs.append(champ.split('/')[-1])
	if len(champs) == 0:
		print("No .cor files found")
		quit()

	numbers = []
	n = 0
	for i, champ in enumerate(champs):
		print(f"{i + 1}: {champ}")
	while n < 4:
		i = int(input(("\nPlease choose a champion to include in the test by giving its number: ")))
		if i <= 0 or i > len(champs):
			print("There's no champ with that number. Try again.")
			continue
		else:
			numbers.append(i)
		n += 1
		ans = 'x'
		while n < 4 and ans != 'y' and ans != 'n':
			ans = input("Add more champions? (y/n) ")
		if ans == 'n':
			n = 4

	players = []
	for n in numbers:
		players.append(champs[n - 1] + ".cor")

	print("\nRunning orig corewar...")
	orig = sp.run(["../resources/corewar", "-v", "6"] + ['/'.join([champ_dir, p]) for p in players], \
		capture_output=True, \
		text=True)
	orig_out = orig.stdout

	print("Running test corewar...")
	test = sp.run(["../corewar", "-v", "3"] + ['/'.join([champ_dir, p]) for p in players], \
		capture_output=True, \
		text=True)
	test_out = test.stdout

	return (orig_out, test_out)
	


def main():
	orig_out, test_out = run_corewars()
	orig = orig_out.split('\n')
	test = test_out.split('\n')

	if len(orig) != len(test):
		print("Line counts of outputs do not match!")
		ans = input("continue anyway? (y/n) ")
		if ans.lower() != 'y':
			print("quitting")
			quit()

	print("Starting output parsing...")
	errors_found = parse_outputs(orig, test)
	if not errors_found:
		print("\nTest completed. Outputs do not differ, well done!")
	else:
		print("\nTest completed. Outputs have differences. :(")


if __name__ == "__main__":
	main()
