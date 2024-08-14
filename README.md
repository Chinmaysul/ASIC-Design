# ASIC-Design
This repository is for ASIC course project

## ASSIGNMENT 1: Compilation Of C Program and RISC-V Compilation
### Step: 1
* In the Linux Terminal, create a new C Program file. Here we have used Gedit.

```c 
#include <stdio.h>
    int main() {
    int i, n=1000, sum=0;
    for(i=1; i<n; i++){
      sum = sum + i;
    }
    printf("Sum of first 1000 numbers is %d\n",sum);
    return 0;
}
```

![Screenshot from 2024-08-08 00-59-14](https://github.com/user-attachments/assets/51c6029e-5093-42fa-8901-a7f4e847e206)

* Compile the code in the terminal using a compiler like GCC.

  
### Step: 2
Run the executable program using ./aout.
### Output
The picture below represents the C code and its output

![Screenshot from 2024-08-08 00-59-35](https://github.com/user-attachments/assets/db8fffc0-b4d2-436b-b781-9aed4c956330)



### Now we will do the RISC-V compilation
### Step: 3

* Run the following command to create the object file (.o)
  ```bash
  riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o sum.o sum.c
  ```
![Screenshot from 2024-08-08 01-00-25](https://github.com/user-attachments/assets/b07dba98-5bc9-452c-a651-81ab26dbbc9e)


### Step: 4
* Run the following command to see the instruction output in the terminal window.
  ```bash
  riscv64-unknown-elf-objdump -d sum.o|less
  ```
![Screenshot from 2024-08-08 01-01-32](https://github.com/user-attachments/assets/ec329a23-625d-44ad-ba2d-735c94b97d37)
![Screenshot from 2024-08-08 01-00-43](https://github.com/user-attachments/assets/f29a88a6-f4b7-49f3-a903-0af41e1c934e)


* For the "main" section, we can calculate the number of instructions by counting each individual instruction
![Screenshot from 2024-08-08 01-01-48](https://github.com/user-attachments/assets/3ecff1dc-1ab7-47af-9624-469ced581cc2)

* We can also find the number of instructions by subtracting the address of main with the next command
* Instructions = (00050593 - ff010113)/4 = 14 instructions
  

### Step: 5
* Now compile the code with the flag **-Ofast** while compiling
![Screenshot from 2024-08-08 01-02-23](https://github.com/user-attachments/assets/5ca864e1-31e3-4403-9554-16269c860508)

* Now we can again count the number of instructions in "main". We can observe the reduction in steps using **-Ofast**
* Instructions = (ffff0797 - 0007a5b7)/4 = 11 instructions
![Screenshot from 2024-08-08 01-02-47](https://github.com/user-attachments/assets/39cbe81b-cdb1-491f-95d0-6f56f384c916)


## ASSIGNMENT 2: RISC-V Compiler Debugging

* We will find the output of the C program on the RISC V Compiler using the Spike command to find the result of n numbers


### Step: 1
* Code for creating spike objdump file:
```bash
spike pk sum.o
```

*  We can observe the output for spike
### The compiled code using SPIKE command along with object dump file
![Screenshot from 2024-08-08 01-49-10](https://github.com/user-attachments/assets/80e4e512-0491-4b1d-8863-9b6f9efade5f)

### Step: 2
* Run this command to debug using spike
```bash
spike -d pk sum.o
```
* We will run the Spike debugger until the main function, which starts at address **100b0**. 
```bash
until pc 0 100b0
```
* After that, we manually debug the register in the next address which is the a1 register before and after the step.
```bash
reg 0 a1
```
Next, we will manually debug the next instruction i.e., addi sp, sp, -16. Before this step, the sp register shows 0x0000003ffffffb50, which then changes to 0x0000003ffffffb40.
```bash
reg 0 sp
```
![Screenshot from 2024-08-08 02-13-53](https://github.com/user-attachments/assets/59ad2f91-34af-4aa1-b400-9007c4a8d0ac)


## Step: 3
* The same thing happens for -O1
![Screenshot from 2024-08-08 02-29-56](https://github.com/user-attachments/assets/7d025656-7fef-4081-bf9e-0f383192e1a4)

```bash
until pc 0 10184
reg 0 sp
```
![Screenshot from 2024-08-08 02-28-08](https://github.com/user-attachments/assets/d63d279c-5435-4204-9d5c-ce9bbec6e56c)

## ASSIGNMENT 3
### 1. Identifying Instruction Type

Instruction formats act as an agreement between assembly language and hardware, ensuring that when an instruction is issued in assembly language, the hardware knows exactly how to execute it. These instructions are represented by sequences of 0s and 1s, which define things like the operation to be performed and where the data is located. This way, the hardware can accurately understand and carry out the instructions.

There are 6 types of instruction formats:

* R type

    + It is also called the Register type.
    +  It is used for instructions with three registers like Arithmetic and Logical instructions.
    +  R-type instructions include fields for 2 source registers, 1 destination register, a funct for specifying the operation, as well as an Opcode.
    +  Examples: ADD, AND, XNOR.
  
  ![Screenshot from 2024-08-08 02-28-08](https://github.com/user-attachments/assets/518e5b3b-046d-452b-90a4-4dc22a78accf)
* I type

    +  I type performs Arithmetic operations with immediate values.
    +  The I-type instructions include a destination register, a source register, an integer value, funct code, and an opcode.
    +  Example: Load, Branch etc.
  
  ![Screenshot from 2024-08-08 02-28-08](https://github.com/user-attachments/assets/044814e2-9f7b-453a-8541-d2650c4e15ab)
  
* S Type 
  
   + S-type instruction is used for store operations, to write a value into the memory.
   + The S-type instruction has 2 source registers, an immediate integer which stores the offset for the memory, a funct code, and an opcode.
     
  ![Screenshot from 2024-08-08 02-28-08](https://github.com/user-attachments/assets/6d2c61ec-2ab2-46f3-98a7-a351d43387a2)


* B-Type Instructions

     + B-type instructions are used for conditional branching. These instructions help control the flow of execution by making decisions based on comparisons between two registers.
     + The B-type format includes fields for two source registers, an immediate value that determines the branch offset, a function code, and an opcode.
  
  ![Screenshot from 2024-08-08 02-28-08](https://github.com/user-attachments/assets/f8c4c251-9d0e-43bb-bc2d-5d62f6546a94)

* U-Type Instructions

    + U-type instructions handle operations that require large immediate values. They're primarily used for loading upper immediate values or calculating addresses.
    + The U-type format includes a destination register, a large immediate value, and an opcode.
  
  ![Screenshot from 2024-08-08 02-28-08](https://github.com/user-attachments/assets/27da568d-cc13-49f7-b291-fe9bec1e0a0f)

* J-Type Instructions

  + J-type instructions are used for jump operations, allowing the program to change control flow by jumping to a specific address.
  + These instructions are common for unconditional jumps, such as function calls or loop implementations.
  
  ![Screenshot from 2024-08-08 02-28-08](https://github.com/user-attachments/assets/d2b575bf-f23f-4064-8cce-015d24a712c4)

   
  

### 2. RISC-V Instruction Breakdown

#### ADD `r5, r4, r5`
- **Instruction Type:** R-Type
- **Opcode:** `0110011`
- **Destination Register (rd):** `r5 (00101)`
- **Source Register 1 (rs1):** `r4 (00100)`
- **Source Register 2 (rs2):** `r5 (00101)`
- **Function Code (func3):** `000`
- **Function Code (func7):** `0000000`
- **Binary Instruction:** `0000000 00101 00100 000 00101 0110011`
- **Hexadecimal Code:** `0x005202b3`

#### SUB `r5, r5, r4`
- **Instruction Type:** R-Type
- **Opcode:** `0110011`
- **Destination Register (rd):** `r5 (00101)`
- **Source Register 1 (rs1):** `r5 (00101)`
- **Source Register 2 (rs2):** `r4 (00100)`
- **Function Code (func3):** `000`
- **Function Code (func7):** `0100000`
- **Binary Instruction:** `0100000 00100 00101 000 00101 0110011`
- **Hexadecimal Code:** `0x404282b3`

#### AND `r4, r5, r5`
- **Instruction Type:** R-Type
- **Opcode:** `0110011`
- **Destination Register (rd):** `r4 (00100)`
- **Source Register 1 (rs1):** `r5 (00101)`
- **Source Register 2 (rs2):** `r5 (00101)`
- **Function Code (func3):** `111`
- **Function Code (func7):** `0000000`
- **Binary Instruction:** `0000000 00101 00101 111 00100 0110011`
- **Hexadecimal Code:** `0x0052f233`

#### OR `r8, r4, r5`
- **Instruction Type:** R-Type
- **Opcode:** `0110011`
- **Destination Register (rd):** `r8 (01000)`
- **Source Register 1 (rs1):** `r4 (00100)`
- **Source Register 2 (rs2):** `r5 (00101)`
- **Function Code (func3):** `110`
- **Function Code (func7):** `0000000`
- **Binary Instruction:** `0000000 00101 00100 110 01000 0110011`
- **Hexadecimal Code:** `0x005222b3`

#### XOR `r8, r5, r4`
- **Instruction Type:** R-Type
- **Opcode:** `0110011`
- **Destination Register (rd):** `r8 (01000)`
- **Source Register 1 (rs1):** `r5 (00101)`
- **Source Register 2 (rs2):** `r4 (00100)`
- **Function Code (func3):** `100`
- **Function Code (func7):** `0000000`
- **Binary Instruction:** `0000000 00100 00101 100 01000 0110011`
- **Hexadecimal Code:** `0x0042e2b3`

#### SLT `r10, r2, r4`
- **Instruction Type:** R-Type
- **Opcode:** `0110011`
- **Destination Register (rd):** `r10 (01010)`
- **Source Register 1 (rs1):** `r2 (00010)`
- **Source Register 2 (rs2):** `r4 (00100)`
- **Function Code (func3):** `010`
- **Function Code (func7):** `0000000`
- **Binary Instruction:** `0000000 00100 00010 010 01010 0110011`
- **Hexadecimal Code:** `0x004151b3`

#### ADDI `r12, r3, 5`
- **Instruction Type:** I-Type
- **Opcode:** `0010011`
- **Destination Register (rd):** `r12 (01100)`
- **Source Register 1 (rs1):** `r3 (00011)`
- **Immediate (imm[11:0]):** `5 (000000000101)`
- **Function Code (func3):** `000`
- **Binary Instruction:** `000000000101 00011 000 01100 0010011`
- **Hexadecimal Code:** `0x005181b3`

#### SW `r3, r1, 4`
- **Instruction Type:** S-Type
- **Opcode:** `0100011`
- **Source Register 2 (rs2):** `r3 (00011)`
- **Source Register 1 (rs1):** `r1 (00001)`
- **Immediate (imm[11:0]):** `4 (000000000100)`
- **Function Code (func3):** `010`
- **Binary Instruction:** `0000000 00011 00001 010 00000 0100011`
- **Hexadecimal Code:** `0x0040a123`

#### SRL `r16, r11, r2`
- **Instruction Type:** R-Type
- **Opcode:** `0110011`
- **Destination Register (rd):** `r16 (10000)`
- **Source Register 1 (rs1):** `r11 (01011)`
- **Source Register 2 (rs2):** `r2 (00010)`
- **Function Code (func3):** `101`
- **Function Code (func7):** `0000000`
- **Binary Instruction:** `0000000 00010 01011 101 10000 0110011`
- **Hexadecimal Code:** `0x0022d803`

#### BNE `r0, r1, 20`
- **Instruction Type:** B-Type
- **Opcode:** `1100011`
- **Source Register 1 (rs1):** `r0 (00000)`
- **Source Register 2 (rs2):** `r1 (00001)`
- **Immediate (imm[12:1]):** `20 (000000010100)`
- **Function Code (func3):** `001`
- **Binary Instruction:** `0 000001 00001 00000 001 0100 0 1100011`
- **Hexadecimal Code:** `0x00100063`

#### BEQ `r0, r0, 15`
- **Instruction Type:** B-Type
- **Opcode:** `1100011`
- **Source Register 1 (rs1):** `r0 (00000)`
- **Source Register 2 (rs2):** `r0 (00000)`
- **Immediate (imm[12:1]):** `15 (000000001111)`
- **Function Code (func3):** `000`
- **Binary Instruction:** `0 000000 00000 00000 000 1111 0 1100011`
- **Hexadecimal Code:** `0x00000f63`

#### LW `r13, r11, 2`
- **Instruction Type:** I-Type
- **Opcode:** `0000011`
- **Destination Register (rd):** `r13 (01101)`
- **Source Register 1 (rs1):** `r11 (01011)`
- **Immediate (imm[11:0]):** `2 (000000000010)`
- **Function Code (func3):** `010`
- **Binary Instruction:** `0000000 00010 01011 010 01101 0000011`
- **Hexadecimal Code:** `0x0022a683 `

#### SLL `r15, r11, r2`
- **Instruction Type:** R-Type
- **Opcode:** `0110011`
- **Destination Register (rd):** `r15 (01111)`
- **Source Register 1 (rs1):** `r11 (01011)`
- **Source Register 2 (rs2):** `r2 (00010)`
- **Function Code (func3):** `001`
- **Function Code (func7):** `0000000`
- **Binary Instruction:** `0000000 00010 01011 001 01111 0110011`
- **Hexadecimal Code:** `0x0022d7b3`
  
* **Instruction Summary Table**

| **Instruction**      | **Type** | **Binary Code**                       | Standard RISC-V       | Hardcoded RISC-V       |
|----------------------|----------|---------------------------------------|------------------------|-----------------------|
| `ADD r5, r4, r5`     | R-Type   | `0000000 00101 00100 000 00101 0110011` | 32'h005202b3             | 32'h02510280             |
| `SUB r5, r5, r4`     | R-Type   | `0100000 00100 00101 000 00101 0110011` | 32'h404282b3             | 32'h02429280             |
| `AND r4, r5, r5`     | R-Type   | `0000000 00101 00101 111 00100 0110011` | 32'h0052f233             | 32'h0250a300             |
| `OR r8, r4, r5`      | R-Type   | `0000000 00101 00100 110 01000 0110011` | 32'h005222b3             | 32'h02512480             |
| `XOR r8, r5, r4`     | R-Type   | `0000000 00100 00101 100 01000 0110011` | 32'h0042e2b3             | 32'h02412480             |
| `SLT r10, r2, r4`    | R-Type   | `0000000 00100 00010 010 01010 0110011` | 32'h004151b3             | 32'h02415580             |
| `ADDI r12, r3, 5`    | I-Type   | `000000000101 00011 000 01100 0010011`  | 32'h005181b3             | 32'h00510600             |
| `SW r3, r1, 4`       | S-Type   | `0000000 00011 00001 010 00000 0100011` | 32'h0040a123             | 32'h00409181             |
| `SRL r16, r11, r2`   | R-Type   | `0000000 00010 01011 101 10000 0110011` | 32'h0022d803             | 32'h00271803             |
| `BNE r0, r1, 20`     | B-Type   | `0 000001 00001 00000 001 0100 0 1100011` | 32'h00100063             | 32'h01400002             |
| `BEQ r0, r0, 15`     | B-Type   | `0 000000 00000 00000 000 1111 0 1100011` | 32'h00000f63             | 32'h00f00002             |
| `LW r13, r11, 2`     | I-Type   | `0000000 00010 01011 010 01101 0000011`  | 32'h0022a683             | 32'h00228681             |
| `SLL r15, r11, r2`   | R-Type   | `0000000 00010 01011 001 01111 0110011` | 32'h0022d7b3             | 32'h00228783             |

* **Hardcoded ISA Table**
  
  | **Operation**  | **Hardcoded ISA** | 
  |----------------|-------------------|
  | `ADD r6, r1, r2` | 32'h02208300 | 
  | `SUB r7, r1, r2` | 32'h02209380 | 
  | `AND r8, r1, r3` | 32'h0230a400 | 
  | `OR r9, r2, r5`  | 32'h02513480 | 
  | `XOR r10, r1, r4` | 32'h0240c500 |
  | `SLT r1, r2, r4` | 32'h02415580 | 
  | `ADDI r12, r4, 5` | 32'h00520600 |
  | `BEQ r0, r0, 15` | 32'h00f00002 | 
  | `SW r3, r1, 2`   | 32'h00209181 | 
  | `LW r13, r1, 2`  | 32'h00208681 | 
  | `SRL r16, r14, r2` | 32'h00271803 | 
  | `SLL r15, r1, r2` | 32'h00208783 |

  * The following are the Hardcoded instrustion set
 
  ![Screenshot from 2024-08-11 15-17-28](https://github.com/user-attachments/assets/196a0800-337a-499a-8d72-24ebdd12bc22)


### 3. GTKWave of the ISA Instructions
#### Step 1: Create a verilog file and testbench
```bash
gedit rv32.v
gedit rv32_tb.v
```
![Screenshot from 2024-08-11 14-53-00](https://github.com/user-attachments/assets/6fa644ab-8aea-4ced-a172-36a70337d552)


#### Step 2: Create the dump file
```bash
iverilog -o rv32 rv32.v rv32_tb.v
./rv32
```
#### Step 3: Run GTKWave
```bash
gtkwave iiitb_rv32i.vcd
```
![Screenshot from 2024-08-11 14-55-40](https://github.com/user-attachments/assets/65e846dc-9a5c-40ab-a872-b64c4644b11e)

#### Waveforms:

* `ADD R6, R2, R1`
  
![Screenshot from 2024-08-11 15-10-31](https://github.com/user-attachments/assets/33de7e9b-f9e4-4f5d-8843-9fd8c439a57c)


* `SUB R7, R1, R2`
  
![Screenshot from 2024-08-11 15-10-44](https://github.com/user-attachments/assets/b93619cb-4abf-48f5-8f0c-c5e3ebd2bf80)


* `AND R8, R1, R3`
  
![Screenshot from 2024-08-11 15-10-50](https://github.com/user-attachments/assets/c85743ce-e13e-4d33-a3aa-ed8c2241de99)


* `OR R9, R2, R5`
  
![Screenshot from 2024-08-11 15-10-56](https://github.com/user-attachments/assets/d18b4972-ca4e-4ba2-b7fe-6f49b05c9f3f)


* `XOR R10,R1,R4`
  
 ![Screenshot from 2024-08-11 15-11-02](https://github.com/user-attachments/assets/d65db59b-21da-4e2f-9da8-6b9c384482c2)


* `SLT R1, R2, R4`
  
  ![Screenshot from 2024-08-11 15-11-09](https://github.com/user-attachments/assets/c70a6bde-834d-4851-8eb5-7f5b54508257)

* `ADDI R12, R4, 5 `
  
![Screenshot from 2024-08-11 15-11-15](https://github.com/user-attachments/assets/fe8cc0c7-b22a-46c2-a6bb-837ca7c73837)


* `BEQ R0, R0, 15`
  
![Screenshot from 2024-08-11 15-14-43](https://github.com/user-attachments/assets/32f8b087-574d-4292-8c98-c7b612666be7)


* `SW R3, R1, 2 `
  
![Screenshot from 2024-08-11 15-14-20](https://github.com/user-attachments/assets/935a8d30-2042-4e6e-8d6d-06caee90f39c)


* `LW R13, R1, 2`
  
![Screenshot from 2024-08-11 15-14-36](https://github.com/user-attachments/assets/672f4818-05c5-4262-9b26-5fdacc1690a5)

## ASSIGNMENT 4
### Complie C code with GCC and RISC-V: Linear search
```c
#include <stdio.h>

int linearSearch(int* arr, int size, int key) {
  
    // Starting the loop and looking for the key in arr
    for (int i = 0; i < size; i++) {

        // If key is found, return key
        if (arr[i] == key) {
            return i;
        }
    }

    // If key is not found, return some value to indicate
    // end
    return -1;
}

int main() {
    int arr[9] = { 10, 50, 30, 70, 80, 60, 20, 90, 40 };
    int size = sizeof(arr) / sizeof(arr[0]);
    int key = 30;

    // Calling linearSearch
    int index = linearSearch(arr, size, key);

    // printing result based on value returned by
    // linearSearch()
    if (index == -1) {
        printf("The element is not present in the arr.");
    }
    else {
        printf("The element is present at arr[%d].", index);
    }

    return 0;
}

```

#### Step 1: Create the C file and compile using GCC

![Screenshot from 2024-08-14 23-03-23](https://github.com/user-attachments/assets/48e2157f-27a6-4f54-b5ad-45c8c96e5a32)
![Screenshot from 2024-08-14 23-03-38](https://github.com/user-attachments/assets/66fd39b9-eb22-44d4-9121-d655563dbf89)


#### Step 2: Compile the code with RISC-V Compiler
```bash
riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o code.o code.c
spike pk code.o
```
![Screenshot from 2024-08-14 23-10-07](https://github.com/user-attachments/assets/135fd3c2-ddf6-423e-b974-90735274a16a)

#### Step 3: Create the obj file and dump it
```bash
riscv64-unknown-elf-objdump -d sum.o|less
```
![Screenshot from 2024-08-14 23-09-34](https://github.com/user-attachments/assets/94add241-f1f0-40d0-a6bb-d32af38a1e6f)

![Screenshot from 2024-08-14 23-09-37](https://github.com/user-attachments/assets/6519379a-e9f8-4d05-95ad-a4f21e81dbf9)








