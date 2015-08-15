""" Raghav Passi(@grebnesieh)'s solution """
def move(A, B, C):
	#print "A = %s B = %s C = %s"%(A,B,C)
	if not A and not B:
		if C == S:
			count[0] += 1
		distinct.add(C)
	else:
		if A:
			move(A[1:], B + A[0], C)
		if B:
			move(A, B[:-1], C + B[-1])

S, distinct, count = raw_input(), set(),[0]
move(S, "", "")
print count[0], len(distinct)
