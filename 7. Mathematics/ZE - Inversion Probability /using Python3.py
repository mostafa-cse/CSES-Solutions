import sys
from decimal import Decimal, getcontext, ROUND_HALF_EVEN

getcontext().prec = 100

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    try:
        n = int(next(iterator))
        r = [int(next(iterator)) for _ in range(n)]
    except StopIteration:
        return

    expected_inversions = Decimal(0)

    for i in range(n):
        for j in range(i + 1, n):
            R_i = Decimal(r[i])
            R_j = Decimal(r[j])

            if R_i <= R_j:
                prob = (R_i - 1) / (2 * R_j)
            else:
                prob = (2 * R_i - R_j - 1) / (2 * R_i)

            expected_inversions += prob

    final_ans = expected_inversions.quantize(Decimal("0.000001"), rounding=ROUND_HALF_EVEN)
    print(final_ans)

if __name__ == "__main__":
    solve()
