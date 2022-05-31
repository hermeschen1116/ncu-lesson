def least_num_bill(bill_list, target_change_prams):
    bill_list.sort()
    bill_list.reverse()
    num_bill = []
    for b in range(len(bill_list)):
        num_bill.append(0)
        cur_change = target_change_prams
        for j in range(b, len(bill_list)):
            if cur_change > 0:
                num_bill[b] += cur_change // bill_list[j]
                cur_change %= bill_list[j]
            else:
                break
    return min(num_bill)


for i in range(int(input())):
    num_bills, target_change = map(int, input().split(' '))
    bills = list(map(int, input().split(' ')))
    print(least_num_bill(bills, target_change))
