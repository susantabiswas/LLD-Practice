# Splitwise

## Requirements
- Show all borrowings for an user
- Show all borrowings for all users
- Track an user's transactions
- Money split options:
  - Equal: Equally split amongst the participants
  - Percentage: Each person pays x % of amount. Check: Total sum of %s = 100
  - Exact: Each user pays the amount assigned to them. Check: Sum of each person's share = Total amount
- Each transaction can have data like name, notes, pic etc
- [Optional] Simplify Expenses:
  If there is a graph of users. Where each user is connected to another because they owe money.
  x [1000] -> y [400] -> z [100] -> a
              |[600]
              b
    [Amount] represents the money owed 
    x will pay: b(600), z(300), a (100)

    x [1000] -> y [1400] -> z [100] -> a
              |[600]
              b
    x will pay: y(1000). 
    We only simplify payment if that reduces the no. of people the direct receipient has to pay.
    Here x could have paid y(400) + b(600). But then y still has to pay the same no. of people.
  
- [Optional] Settle up borrowings
- [Optional] Create Expense Groups with metadata