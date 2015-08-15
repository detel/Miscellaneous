size = input()
heights = map(int, raw_input().split())
max_area, i = 0, 0
stack = []

while i < size:
	if not stack or heights[i] >= heights[stack[-1]]:
		stack.append(i)
		i += 1
	else:
		top = stack.pop()
		max_area = max(max_area, heights[top]*(i-1-stack[-1] if stack else i))
		
while stack:
	top = stack.pop()
	max_area = max(max_area, heights[top]*(i-1-stack[-1] if stack else i))

print max_area
