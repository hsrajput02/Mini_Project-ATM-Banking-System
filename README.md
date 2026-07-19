#  ATM Banking System in C

A simple ATM Banking System developed in **C Programming** using **Structures**, **Functions**, and **Binary File Handling**. This project simulates the basic working of an ATM where customers can securely log in using their account number and PIN to perform banking operations.

##  Features

### Bank Module (`account_setup.c`)
- Create New Customer Account
- Generate Unique Account Number
- Set 4-Digit PIN
- Opening Balance
- View All Customer Accounts
- Store Customer Data in `bank.dat`

### ATM Module (`main.c`)
- Secure Login (Account Number + PIN)
- Balance Inquiry
- Deposit Money
- Withdraw Money
- Transfer Money
- Change PIN
- Mini Statement
- Logout
- Automatic Data Saving

---

##  Technologies Used

- C Programming
- Structures
- Functions
- Arrays
- File Handling (Binary Files)
- Conditional Statements
- Loops
- Switch Case

---

##  Project Structure

```
ATM-Banking-System/
│
├── account_setup.c      # Bank Employee Module
├── main.c               # ATM Module
├── bank.dat             # Customer Database
├── README.md
├── .gitignore
└── screenshots/
```

---

##  How to Run

### Step 1: Clone the Repository

```bash
git clone https://github.com/your-username/ATM-Banking-System.git
```

---

### Step 2: Compile Bank Module

```bash
gcc account_setup.c -o account_setup
```

Run:

```bash
./account_setup
```

Create customer accounts.

---

### Step 3: Compile ATM Module

```bash
gcc main.c -o atm
```

Run:

```bash
./atm
```

Login using the account number and PIN created in the Bank Module.

---

##  Data Storage

All customer information is stored in a binary file named **bank.dat**.

Each customer record contains:

- Account Number
- Customer Name
- 4-Digit PIN
- Account Balance

The ATM module reads customer records from `bank.dat`, performs transactions, and writes the updated information back to the same file.

---

##  Workflow

```
Bank Employee
      │
      ▼
account_setup.c
      │
Create Customer Accounts
      │
      ▼
   bank.dat
      │
      ▼
    main.c
      │
Customer Login
      │
      ▼
ATM Services
      │
      ▼
Update Customer Data
      │
      ▼
Save to bank.dat
```

---

##  Screenshots

Add screenshots here after running the project.

- Account Creation
- Login Screen
- ATM Menu
- Deposit
- Withdrawal
- Transfer Money
- Mini Statement

---

##  Learning Outcomes

This project demonstrates:

- Structures in C
- Functions
- Arrays
- Binary File Handling
- Menu-Driven Programming
- Authentication using PIN
- Data Persistence
- Modular Programming

---

##  Future Improvements

- Admin Login
- Transaction History
- Account Deletion
- Account Search
- Interest Calculation
- Loan Management
- Password Encryption
- Date & Time Stamps
- Receipt Generation

---

##  Author

**Harpal Singh Lodhi**

B.Tech Computer Science & Engineering (AI)

Greater Noida College of Technology

---

##  License

This project is developed for educational purposes as a C Programming Mini Project.