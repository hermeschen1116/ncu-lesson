def least_num_bill(bill_list, target_change_prams):
    if len(bill_list) != 0 and target_change_prams != 0:
        bill_list.sort(reverse=True)
        num_bill = [0]
        for dollar in range(target_change_prams):
            num_bill.append(float('inf'))
        for dollar in range(1, target_change_prams+1):
            for bill in bill_list:
                if dollar >= bill:
                    num_bill[dollar] = min([num_bill[dollar - bill] + 1, num_bill[dollar]])

        return num_bill[target_change_prams]


for i in range(int(input())):
    num_bills, target_change = map(int, input().split(' '))
    bills = list(map(int, input().split(' ')))
    print(least_num_bill(bills, target_change))
