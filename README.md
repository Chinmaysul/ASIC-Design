# ASIC-Design
This repository is for ASIC course project
<details>
<summary> Pre MidTerm </summary>
    
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
### Description: Linear Search in Array
This code searches the element present in the array and returns its position in the array otherwise prints not present.
- The code contains an array arr of size 9
- The number to search for in the array is called key
- The program performs linear search in the array and returns the position of the array if the key is present
- If the key is not present it returns the message "The element is not present in the arr."
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


## ASSIGNMENT 5

### About Makerchip
Makerchip brings support for Transaction-Level Verilog (TL-Verilog), a next-generation approach to hardware design. TL-Verilog simplifies the process by getting rid of the complexities of traditional Verilog and introducing a clearer, more straightforward syntax. It includes robust features for managing pipelines and transactions, which makes it easier to create intricate digital circuits and boosts design efficiency overall.

### Combinatorial Ciruit using TL-Verilog
![all-gates-truth-table](https://github.com/user-attachments/assets/c474c120-c552-4b99-bee4-e1b3abe4cb33)

Below are the combinatorial circuits simulated in Makerchip:

* **Inverter- NOT Gate**
  ```tl-verilog 
   $out = ! $in;
  ```
  ![Screenshot from 2024-08-21 00-31-43](https://github.com/user-attachments/assets/e9223eaf-43f3-4244-8096-4d93f6dcafea)

* **2 Input AND Gate**
  ```tl-verilog
  $out = $in1 && $in2;
  ```
  ![Screenshot from 2024-08-21 00-32-56](https://github.com/user-attachments/assets/725fb74f-ab92-4213-b2f4-804726d1df7c)

* **2 Input OR Gate**
   ```tl-verilog
   $out = $in1 || $in2;
   ```
   ![Screenshot from 2024-08-21 00-33-59](https://github.com/user-attachments/assets/e1a1a156-3072-469e-bfa5-5d667c782b78)

* **2 Input XOR Gate**
  ```tl-verilog
   $out = $in1 ^ $in2;
   ```
  ![Screenshot from 2024-08-21 00-34-38](https://github.com/user-attachments/assets/c06713a7-9b71-4d4f-ac58-54b40fe8f5d2)

* **2:1 Mux**
  ```tl-verilog
   $out = $sel ? $in1 : $in0;
  ```
  ![Screenshot from 2024-08-21 00-36-02](https://github.com/user-attachments/assets/dbe2f221-1467-4547-8a35-8dd3419f0e4e)

* **2:1 Mux on Vectors**
  ```tl-verilog
   $out[7:0] = $sel ? $in1[7:0] : $in0[7:0];
  ```
  ![Screenshot from 2024-08-21 00-36-38](https://github.com/user-attachments/assets/68f5ab66-0f32-4200-8acb-ceeb7a110694)

* **Arithmetic Operations ( Addition)**
  
  This performs the addition operation on the variables $in1[3:0] and $in2[3:0]
  
  ```tl-verilog
   $out[4:0] = $in1[3:0] + $in2[3:0];
  ```
  ![Screenshot from 2024-08-21 00-35-15](https://github.com/user-attachments/assets/a2ea73eb-f0a9-4178-ae4c-4d5d363e3858)

* **Combinational Calculator in TL-Verilog**

   ```tl-verilog
    $num1[31:0] = $rand1[3:0];
    $num2[31:0] = $rand2[3:0];
    
    $sum[31:0]  = $num1[31:0] + $num2[31:0];
    $diff[31:0] = $num1[31:0] - $num2[31:0];
    $prod[31:0] = $num1[31:0] * $num2[31:0];
    $div[31:0] = $num1[31:0] / $num2[31:0];
    $out[31:0]  = $sel[1] ? ($sel[0] ? $div[31:0] : $prod[31:0]): ($sel[0] ? $diff[31:0] : $sum[31:0]);
   ```

In the provided code, two random 4-bit values, $rand1[3:0] and $rand2[3:0], are assigned to 32-bit variables $num1[31:0] and $num2[31:0], respectively. The calculator then carries out the four arithmetic operations on these values: addition, subtraction, multiplication and division.

A multiplexer (MUX), controlled by the selection bits $sel[1:0], is used to choose one of these operations. The MUX determines which operation's result is sent to the output variable $out[31:0].
    
  ![Screenshot from 2024-08-21 00-42-29](https://github.com/user-attachments/assets/cca10691-31f7-424f-a798-8b80cdf18924)

  
### Sequential Circuits using TL-Verilog

A sequential circuit is a type of digital circuit that incorporates memory elements to store data, allowing it to produce outputs based on both the current inputs and its previous states. Unlike combinational circuits, where the output is determined only by the current inputs, sequential circuits take into account past inputs through feedback loops and storage components like flip-flops or registers. These components help the circuit maintain an internal state over time, which, along with the current input, influences its behavior. This capability enables sequential circuits to perform functions that require tracking past inputs or operations, such as counting, data storage, or event sequencing.

#### Counter Circuit:
It increments the value by 1 in each iteration

```tl-verilog
$reset = *reset;
$clk_chi = *clk;
$cnt[31:0] = $reset ? 0 : (>>1$cnt + 1);
```

<img width="267" alt="image" src="https://github.com/user-attachments/assets/e68d8794-9938-4380-aeda-c23f2d068cae">
<img width="959" alt="image" src="https://github.com/user-attachments/assets/09ec6961-3928-4047-9e7c-98c16a16967c">

#### Fibonacci Series: 
The Fibonacci series is a sequence of numbers in which each number is the sum of the two preceding ones, usually starting with 0 and 1. The sequence begins as follows:

0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...

```tl-verilog
$reset = *reset;
$clk_chi = *clk;
$num[31:0] = $reset ? 1 : (>>1$num + >>2$num);
```
![Screenshot 2024-08-21 143500](https://github.com/user-attachments/assets/257c9948-fb60-40ba-8f81-7c2aac003c34)

![image](https://github.com/user-attachments/assets/3f5932b9-57d9-439f-a620-1d733fca6ed1)

#### Counter-Output with Calculator Integration:

This code functions like a standard calculator, where the result of the previous operation is used as one of the operands for the next operation. When reset, the result is set back to zero.

```tl-verilog
$reset = *reset;
$clk_chi = *clk;   
$val1[31:0] = >>1$out;
$val2[31:0] = $rand[3:0];
   
$sum[31:0] =  $val1[31:0] +  $val2[31:0];
$diff[31:0] =  $val1[31:0] -  $val2[31:0];
$prod[31:0] =  $val1[31:0] *  $val2[31:0];
$quot[31:0] =  $val1[31:0] /  $val2[31:0];
$out[31:0] = $reset ? 32'h0 : ($choose[1] ? ($choose[0] ? $quot : $prod):($choose[0] ? $diff : $sum));

```

![image](https://github.com/user-attachments/assets/0b8ed2c4-eff2-4471-a436-8b8953b89799)


### Pipelined Logic
In Transaction-Level Verilog (TL-Verilog), pipelined logic is effectively represented using pipeline constructs that naturally depict the flow of data through various stages of a digital design. Each stage in a TL-Verilog pipeline corresponds to a clock cycle, where data is processed as it moves through the pipeline. This method allows for clear and straightforward modeling of sequential logic, with each stage automatically managing the propagation of state and values to the subsequent cycle. By utilizing TL-Verilog's pipeline notation, designers can easily describe complex, multi-stage operations, focusing on transaction flow, which simplifies the design and verification process while improving readability and maintainability.

 <img width="898" alt="14" src="https://github.com/user-attachments/assets/cef07766-78a1-4b64-8593-cdea8b621a0a">

I've included the simulation for the pipelined logic below. 

```tl-verilog
$reset = *reset;
$clk_chi = *clk;
|comp
  @1
    $err1 = $bad_input || $illegal_op;
  @3
    $err2 = $over_flow || $err1;
  @6
    $err3 = $div_by_zero || $err2;
```

 ![image](https://github.com/user-attachments/assets/ef3f104c-aa94-4691-a515-1d3c15772e5e)

#### Cycle Calculator

```tl-verilog
$reset = *reset;
$clk_chi = *clk;
|calc
  @1
    $reset = *reset;
    $clk_chi = *clk;
   
    $val1[31:0] = >>2$out[31:0];
    $val2[31:0] = $rand2[3:0];
    $sel[1:0] = $rand3[1:0];
   
    $sum[31:0] = $val1[31:0] + $val2[31:0];
    $diff[31:0] = $val1[31:0] - $val2[31:0];
    $prod[31:0] = $val1[31:0] * $val2[31:0];
    $quot[31:0] = $val1[31:0] / $val2[31:0];
         
    $count = $reset ? 0 : >>1$count + 1;
         
  @2
    $valid = $count;
    $inv_valid = !$valid;
    $calc_reset = $reset | $inv_valid;
    $out[31:0] = $calc_reset ? 32'b0 : ($op[1] ? ($op[0] ? $quot[31:0] : $prod[31:0]): ($op[0] ? $diff[31:0] : $sum[31:0]));

```

The simulation for the cycle calculator is shown below.

![image](https://github.com/user-attachments/assets/de9f23b8-cde2-45ea-8ade-bad191e45d1b)

 
<img width="488" alt="16" src="https://github.com/user-attachments/assets/fa30363a-f7a0-45c2-8ac4-ca95806ce18a">

#### Validity

When generating a waveform, we typically receive results for every clock cycle, just as in previous examples. Although there may be no compilation errors, logical errors can still occur, which won't be detected during compilation. These errors can be difficult to identify simply by analyzing the waveforms. Additionally, there may be scenarios where "don't care" conditions arise, which are irrelevant and should be ignored. To address this, we use the concept of validity.

The global clock runs continuously, and there may be cases in our code where certain operations are triggered by the clock even though they aren't needed. Physically, running the clock requires power from voltage or current sources during each cycle. In complex circuits, failing to manage these unnecessary operations can lead to wasted power. To minimize power consumption, we disable the clock during these unnecessary cycles, a technique known as clock gating. Validity is essential for implementing this process.

* **Cycle Calculator**

```tl-verilog
$reset = *reset;
   $clk_div = *clk;
   
   |cal
      @1
         $reset = *reset;
         $clk_div = *clk;
         
         $cnt[31:0] = $reset ? 0 : (>>1$cnt + 1);
         $valid = $cnt;
         $valid_or_reset = ($reset | $valid);
         
      
      ?$valid
         @1
            $val1[31:0] = >>2$out;
            $val2[31:0] = $rand2[3:0];
            
            $sum[31:0]  = $val1[31:0] + $val2[31:0];
            $diff[31:0] = $val1[31:0] - $val2[31:0];
            $prod[31:0] = $val1[31:0] * $val2[31:0];
            $quot[31:0] = $val1[31:0] / $val2[31:0];
            
         @2
            $nxt[31:0] = ($sel[1:0] == 2'b00) ? $sum[31:0]:
                         ($sel[1:0] == 2'b01) ? $diff[31:0]:
                         ($sel[1:0] == 2'b10) ? $prod[31:0]:
                                                $quot[31:0];
            
            $out[31:0] = $valid_or_reset ? 32'h0 : $nxt;

```

![image](https://github.com/user-attachments/assets/4d79c5a9-5431-4f5b-ab9b-26aa7696f61b)

* **Total Distance Calculator**

```tl-verilog
|calc
  @1
    $reset = *reset;
    $clk_chi = *clk;
            
    ?$vaild      
      @1
        $aa_seq[31:0] = $aa[3:0] * $aa;
        $bb_seq[31:0] = $bb[3:0] * $bb;;
      
      @2
        $cc_seq[31:0] = $aa_seq + $bb_seq;;
      
      @3
        $cc[31:0] = sqrt($cc_seq);
            
      @4
         $tot_dist[63:0] = $reset ? 0 : $valid ? >>1$tot_dist + $cc : >>1$tot_dist;

```
![image](https://github.com/user-attachments/assets/90626dc9-94ae-4e9e-aa7a-5d6b00325729)


### RISC-V CPU Implementation

![15](https://github.com/user-attachments/assets/141d5daa-c990-4379-bdbf-235cb6d1dca4)

The design of the RISC-V consists of the following blocks:
- Program Counter
- Instruction Fetch
- Instruction Decode
- Register File Read
- Arithmetic Logic Unit
- Register File Write
- Branch instruction

#### 1. Program Counter  
The Program Counter (PC) is a key register that keeps track of the address of the next instruction to be executed, essentially pointing to the current position in the instruction memory. Since each instruction is 32 bits (or 4 bytes) long in a byte-addressable memory system, the PC increases by 4 after every instruction to point to the next one. When the system starts up, a reset signal initializes the PC to 0, ensuring the first instruction is fetched from the correct starting address. For branch instructions, the PC adds an immediate offset to the current address, calculating the new address as: NextPC = Current PC + Offset. Normally, the PC simply advances by 4 to move to the next instruction, but it will reset to zero if a reset signal is detected. The provided diagram illustrates how the PC moves through instructions and responds to reset signals and branch operations.

```tl-verilog
|cpu
  @0
    $reset = *reset;
    $clk_chi = *clk;
    $pc[31:0] = >>1$reset ? 0 : >>1$pc + 32'd4;
```

<img width="777" alt="2" src="https://github.com/user-attachments/assets/a65385c0-94d3-471f-913e-b580fd4d507f">

![image](https://github.com/user-attachments/assets/7aea7de4-059b-4797-b849-46fb31fbcd8b)

#### 2. Instruction Fetch

The Instruction Fetch Unit (IFU) in a CPU is responsible for ensuring that program instructions are retrieved from memory and executed in the correct order, serving as a crucial part of the core's control logic. The program counter plays a key role by indicating the address of the next instruction that needs to be fetched from the instruction memory. This step is essential for continuing the program’s execution and performing subsequent computations.

In this setup, the instruction memory is integrated into the program, allowing the Instruction Fetch logic to access and retrieve the required instructions. Once an instruction is fetched, it is passed on to the Decode logic for further processing. The program counter provides the read address for the instruction memory, which in turn outputs a 32-bit instruction (instr[31:0]). This sequence ensures that instructions are fetched and processed efficiently, maintaining the flow of the program.

```tl-verilog
|cpu
  @0
    $reset = *reset;
    $clk_chi = *clk;
    $pc[31:0] = $reset ? '0 : >>1$pc + 32'd4;
         
    $imem_rd_en = !$reset ? 1 : 0;
    $imem_rd_addr[M4_IMEM_INDEX_CNT-1:0] = $pc[M4_IMEM_INDEX_CNT+1:2];

  @1
    $instr[31:0] = $imem_rd_data[31:0];
```

![3](https://github.com/user-attachments/assets/a67fcb4b-84ec-476a-bb3c-2a44fae2442d)


![image](https://github.com/user-attachments/assets/fec6c3a7-d322-49f1-8f73-dbb4ae334c76)

#### 3. Instruction Decode
In the decode stage, the main goal is to break down the instruction fetched in the previous stage to extract all necessary details. This process includes identifying the type of instruction, recognizing any immediate values, and retrieving the relevant register values. During Instruction Decode, each instruction is carefully analyzed to determine its category, check for the presence of immediate values, and extract specific fields such as the opcode. The opcode is then matched to its corresponding instruction, and the bit fields are interpreted according to the RISC-V ISA specifications.

**RISC-V Instruction Formats**
RISC-V instruction formats serve as a "contract" between the assembly language and the hardware, ensuring that when an assembly instruction is executed, the hardware knows exactly how to proceed. Each instruction type in RISC-V has a specific format, defined by a sequence of 0s and 1s, which includes details about the operation type and data location. There are six distinct types of instructions in the RISC-V architecture.

![4](https://github.com/user-attachments/assets/484bde35-4fdc-4255-a22a-d5d38c6a495e)

```tl-verilog
 //INSTRUCTION TYPES DECODE         
@1
  $is_u_instr = $instr[6:2] ==? 5'b0x101;
         
  $is_s_instr = $instr[6:2] ==? 5'b0100x;
         
  $is_r_instr = $instr[6:2] ==? 5'b01011 ||
                       $instr[6:2] ==? 5'b011x0 ||
                       $instr[6:2] ==? 5'b10100;
         
  $is_j_instr = $instr[6:2] ==? 5'b11011;
         
  $is_i_instr = $instr[6:2] ==? 5'b0000x ||
                       $instr[6:2] ==? 5'b001x0 ||
                       $instr[6:2] ==? 5'b11001;
         
  $is_b_instr = $instr[6:2] ==? 5'b11000;
         
  //INSTRUCTION IMMEDIATE DECODE
  $imm[31:0] = $is_i_instr ? {{21{$instr[31]}}, $instr[30:20]} :
                      $is_s_instr ? {{21{$instr[31]}}, $instr[30:25], $instr[11:7]} :
                      $is_b_instr ? {{20{$instr[31]}}, $instr[7], $instr[30:25], $instr[11:8], 1'b0} :
                      $is_u_instr ? {$instr[31:12], 12'b0} :
                      $is_j_instr ? {{12{$instr[31]}}, $instr[19:12], $instr[20], $instr[30:21], 1'b0} :
                                    32'b0;
         
         
         
         
         
  //INSTRUCTION FIELD DECODE
  $rs2_valid = $is_r_instr || $is_s_instr || $is_b_instr;
  ?$rs2_valid
    $rs2[4:0] = $instr[24:20];
            
  $rs1_valid = $is_r_instr || $is_i_instr || $is_s_instr || $is_b_instr;
  ?$rs1_valid
    $rs1[4:0] = $instr[19:15];
         
  $funct3_valid = $is_r_instr || $is_i_instr || $is_s_instr || $is_b_instr;
  ?$funct3_valid
    $funct3[2:0] = $instr[14:12];
            
  $funct7_valid = $is_r_instr ;
  ?$funct7_valid
    $funct7[6:0] = $instr[31:25];
  $rd_valid = $is_r_instr || $is_i_instr || $is_u_instr || $is_j_instr;
  ?$rd_valid
    $rd[4:0] = $instr[11:7];
         
         
   //INSTRUCTION DECODE
  $opcode[6:0] = $instr[6:0];
         
  $dec_bits [10:0] = {$funct7[5], $funct3, $opcode};
  $is_beq = $dec_bits ==? 11'bx_000_1100011;
  $is_bne = $dec_bits ==? 11'bx_001_1100011;
  $is_blt = $dec_bits ==? 11'bx_100_1100011;
  $is_bge = $dec_bits ==? 11'bx_101_1100011;
  $is_bltu = $dec_bits ==? 11'bx_110_1100011;
  $is_bgeu = $dec_bits ==? 11'bx_111_1100011;
  $is_addi = $dec_bits ==? 11'bx_000_0010011;
  $is_add = $dec_bits ==? 11'b0_000_0110011;
         
  `BOGUS_USE ($is_beq $is_bne $is_blt $is_bge $is_bltu $is_bgeu $is_addi $is_add)
```

![image](https://github.com/user-attachments/assets/d9cfdf87-24a8-48cd-96b4-65f7a4f8b753)


#### 4. Register File Read

Most instructions, particularly arithmetic ones, require data from source registers, which means the CPU needs to read from these registers. To facilitate this, the CPU's register file is designed to handle two simultaneous reads for the source operands (rs1 and rs2) and one write operation per cycle to the destination register. The register file receives rs1 and rs2 as inputs and outputs the corresponding register values. The enable bits for rs1 and rs2 are activated based on their validity, as determined earlier in the process. This setup, known as a 2-port register file, allows the CPU to read from two registers at the same time. The retrieved data is then stored in registers and sent to the ALU for further processing.

```tl-verilog
//REGISTER FILE READ
$rf_wr_en = 1'b0;
$rf_wr_index[4:0] = 5'b0;
$rf_rd_en1 = $rs1_valid;
$rf_rd_index1[4:0] = $rs1;
$rf_rd_en2 = $rs2_valid;
$rf_rd_index2[4:0] = $rs2;
         
$src1_value[31:0] = $rf_rd_data1;
$src2_value[31:0] = $rf_rd_data2;
```

![Screenshot 2024-08-21 192832](https://github.com/user-attachments/assets/4afb17d8-bb73-494c-89a1-51bdf29d2037)

#### 5. Arithmetic Logic Unit (ALU)

The Arithmetic Logic Unit (ALU) is responsible for carrying out computations based on the specified operation. It receives data from two registers provided by the register file, performs the required arithmetic operation, and then stores the result back into memory via the register file's write port. Currently, the code is configured to support only ADD and ADDI operations to execute the test code.

```tl-verilog
//ARITHMETIC AND LOGIC UNIT (ALU)
$result[31:0] = $is_addi ? $src1_value + $imm :
              $is_add ? $src1_value + $src2_value :
                32'bx ;
```

![image](https://github.com/user-attachments/assets/ae20e7c6-3d02-4a5b-8b40-3cfc237812d1)

#### 6. Register File Write

This step is crucial for handling instructions that need to store the output in a destination register (rd). The result generated by the ALU is written back to memory through the `register_file_write` port, with the `register_file_write_enable` signal activated based on the validity of the destination register (rd). The `register_file_write_index` then directs the value from the destination register (rd) to the correct memory location. In the RISC-V architecture, the x0 register is always set to zero, so an additional condition is included to prevent any write operations to the x0 register. After the ALU completes its operations on the register values, the results are written back to the appropriate registers, ensuring that the x0 register remains unchanged, preserving its value of zero.

```tl-verilog
//REGISTER FILE WRITE
$rf_wr_en = $rd_valid && $rd != 5'b0;
$rf_wr_index[4:0] = $rd;
$rf_wr_data[31:0] = $result;
```

![image](https://github.com/user-attachments/assets/5c84dff4-8e33-4d8b-85f9-0dc933dd214f)

#### 7. Branch instruction

The last stage involves adding support for branch instructions. In the RISC-V instruction set architecture, branches are conditional, so a branch is executed only when a particular condition is fulfilled. Moreover, the target address for the branch (Program Counter or PC) needs to be computed. If the branch condition is met, the PC is updated to this new target address. This ensures that when a branch occurs, the program counter correctly points to the desired instruction.

```tl-verilog
//BRANCH INSTRUCTIONS 1
$taken_branch = $is_beq ? ($src1_value == $src2_value):
$is_bne ? ($src1_value != $src2_value):
$is_blt ? (($src1_value < $src2_value) ^ ($src1_value[31] != $src2_value[31])):
$is_bge ? (($src1_value >= $src2_value) ^ ($src1_value[31] != $src2_value[31])):
$is_bltu ? ($src1_value < $src2_value):
$is_bgeu ? ($src1_value >= $src2_value):
                                    1'b0;
`BOGUS_USE($taken_branch)
         
//BRANCH INSTRUCTIONS 2
 $br_target_pc[31:0] = $pc +$imm;
```

![image](https://github.com/user-attachments/assets/dbf456af-9801-4784-bb26-1c62dbb4a146)

### Final Block Diagram

``` tl-verilog
\m4_TLV_version 1d: tl-x.org
\SV
   // This code can be found in: https://github.com/stevehoover/RISC-V_MYTH_Workshop
   
   m4_include_lib(['https://raw.githubusercontent.com/BalaDhinesh/RISC-V_MYTH_Workshop/master/tlv_lib/risc-v_shell_lib.tlv'])

\SV
   m4_makerchip_module   // (Expanded in Nav-TLV pane.)
\TLV

   // /====================\
   // | Sum 1 to 9 Program |
   // \====================/
   //
   // Program for MYTH Workshop to test RV32I
   // Add 1,2,3,...,9 (in that order).
   //
   // Regs:
   //  r10 (a0): In: 0, Out: final sum
   //  r12 (a2): 10
   //  r13 (a3): 1..10
   //  r14 (a4): Sum
   // 
   // External to function:
   m4_asm(ADD, r10, r0, r0)             // Initialize r10 (a0) to 0.
   // Function:
   m4_asm(ADD, r14, r10, r0)            // Initialize sum register a4 with 0x0
   m4_asm(ADDI, r12, r10, 1011)         // Store count of 10 in register a2.
   m4_asm(ADD, r13, r10, r0)            // Initialize intermediate sum register a3 with 0
   // Loop:
   m4_asm(ADD, r14, r13, r14)           // Incremental addition
   m4_asm(ADDI, r13, r13, 1)            // Increment intermediate register by 1
   m4_asm(BLT, r13, r12, 1111111111000) // If a3 is less than a2, branch to label named <loop>
   m4_asm(ADD, r10, r14, r0)            // Store final result to register a0 so that it can be read by main program
   
   // Optional:
   // m4_asm(JAL, r7, 00000000000000000000) // Done. Jump to itself (infinite loop). (Up to 20-bit signed immediate plus implicit 0 bit (unlike JALR) provides byte address; last immediate bit should also be 0)
   m4_define_hier(['M4_IMEM'], M4_NUM_INSTRS)

   |cpu
      @0
         $reset = *reset;
         $clk_chi = *clk;
         //$pc[31:0] = >>1$reset ? 0 : ( >>1$pc + 31'h4 );
         
         $pc[31:0] = (>>1$reset) ? '0 :
                     (>>1$taken_br) ? >>1$br_tgt_pc : >>1$pc + 32'd4;

         
         $imem_rd_en = >>1$reset ? 0 : 1;
         $imem_rd_addr[M4_IMEM_INDEX_CNT-1:0] = $pc[M4_IMEM_INDEX_CNT+1:2];
         
      @1
         $instr[31:0] = $imem_rd_data[31:0];
         
         //decode
         $is_i_instr = $instr[6:2] ==? 5'b0000x ||
                       $instr[6:2] ==? 5'b001x0 ||
                       $instr[6:2] ==? 5'b11001;
         $is_r_instr = $instr[6:2] ==? 5'b01011 ||
                       $instr[6:2] ==? 5'b011x0 ||
                       $instr[6:2] ==? 5'b10100;
         $is_s_instr = $instr[6:2] ==? 5'b0100x;
         $is_b_instr = $instr[6:2] ==? 5'b11000;
         $is_j_instr = $instr[6:2] ==? 5'b11011;
         $is_u_instr = $instr[6:2] ==? 5'b0x101;
         
         //imm decode
         $imm[31:0] = $is_i_instr ? {{21{$instr[31]}}, $instr[30:20]} :
                      $is_s_instr ? {{21{$instr[31]}}, $instr[30:25], $instr[11:7]} :
                      $is_b_instr ? {{20{$instr[31]}}, $instr[7], $instr[30:25], $instr[11:8], 1'b0} :
                      $is_u_instr ? {$instr[31:12], 12'b0} :
                      $is_j_instr ? {{12{$instr[31]}}, $instr[19:12], $instr[20], $instr[30:21], 1'b0} :
                      32'b0;
         
         //decode logic for other fields
         $rs2_valid = $is_r_instr || $is_s_instr || $is_b_instr;
         ?$rs2_valid
            $rs2[4:0] = $instr[24:20];
            
         $rs1_valid = $is_r_instr || $is_i_instr || $is_s_instr || $is_b_instr;
         ?$rs1_valid
            $rs1[4:0] = $instr[19:15];
         
         $funct3_valid = $is_r_instr || $is_i_instr || $is_s_instr || $is_b_instr;
         ?$funct3_valid
            $funct3[2:0] = $instr[14:12];
            
         $funct7_valid = $is_r_instr ;
         ?$funct7_valid
            $funct7[6:0] = $instr[31:25];
            
         $rd_valid = $is_r_instr || $is_i_instr || $is_u_instr || $is_j_instr;
         ?$rd_valid
            $rd[4:0] = $instr[11:7];
            
         $opcode[6:0] = $instr[6:0];
         $dec_bits[10:0] = {$funct7[5],$funct3,$opcode};
         
         $is_beq = $dec_bits ==? 11'bx_000_1100011;
         $is_bne = $dec_bits ==? 11'bx_001_1100011;
         $is_blt = $dec_bits ==? 11'bx_100_1100011;
         $is_bge = $dec_bits ==? 11'bx_101_1100011;
         $is_bltu = $dec_bits ==? 11'bx_110_1100011;
         $is_bgeu = $dec_bits ==? 11'bx_111_1100011;
         $is_add = $dec_bits ==? 11'b0_000_0110011;
         $is_addi = $dec_bits ==? 11'bx_000_0010011;
         
         //RF read and enable
         $rf_rd_en1 = $rs1_valid;
         $rf_rd_index1[4:0] = $rs1;
         $rf_rd_en2 = $rs2_valid;
         $rf_rd_index2[4:0] = $rs2;
         
         $src1_value[31:0] = $rf_rd_data1;
         $src2_value[31:0] = $rf_rd_data2;
         
         // ALU
         $result[31:0] = $is_addi ? $src1_value + $imm :
                         $is_add ? $src1_value + $src2_value : 32'bx ;
                         
         //RF write and enable
         $rf_wr_en = $rd_valid && $rd != 5'b0;
         $rf_wr_index[4:0] = $rd;
         $rf_wr_data[31:0] = $result;
         
         //branch
         $taken_br = $is_beq ? ($src1_value == $src2_value) :
                     $is_bne ? ($src1_value != $src2_value) :
                     $is_blt ? (($src1_value < $src2_value) ^ ($src1_value[31] != $src2_value[31])) :
                     $is_bge ? (($src1_value >= $src2_value) ^ ($src1_value[31] != $src2_value[31])) :
                     $is_bltu ? ($src1_value < $src2_value) :
                     $is_bgeu ? ($src1_value >= $src2_value) : 1'b0;
         
         $br_tgt_pc[31:0] = $pc + $imm;
         

         
      

      // Note: Because of the magic we are using for visualisation, if visualisation is enabled below,
      //       be sure to avoid having unassigned signals (which you might be using for random inputs)
      //       other than those specifically expected in the labs. You'll get strange errors for these.

   
   // Assert these to end simulation (before Makerchip cycle limit).
   *passed = |cpu/xreg[14]>>5$value == (1+2+3+4+5+6+7+8+9) ;
   *passed = *cyc_cnt > 40;
   *failed = 1'b0;
   
   // Macro instantiations for:
   //  o instruction memory
   //  o register file
   //  o data memory
   //  o CPU visualization
   |cpu
      m4+imem(@1)    // Args: (read stage)
      m4+rf(@1, @1)  // Args: (read stage, write stage) - if equal, no register bypass is required
      //m4+dmem(@4)    // Args: (read/write stage)

   m4+cpu_viz(@4)    // For visualisation, argument should be at least equal to the last stage of CPU logic. @4 would work for all labs.
\SV
   endmodule
```

![image](https://github.com/user-attachments/assets/f5ce3369-1561-48d3-9844-0bcc4b9251ed)

![image](https://github.com/user-attachments/assets/48291f96-30cd-4824-9234-4b215dd92881)

###  Testing the core with a Testbench
With the implementation now complete, a simple testbench statement can be added to verify the functionality of the core. The "passed" and "failed" signals are used to communicate with the Makerchip platform to manage the simulation process. These signals indicate whether the simulation has passed without errors or has failed, in which case the errors can be identified through the log files. If the simulation fails, the "failed" signal instructs the platform to stop the simulation.

```tl-verilog
*passed = |cpu/xreg[10]>>5$value == (1+2+3+4+5+6+7+8+9);
```

![image](https://github.com/user-attachments/assets/96e913f4-759c-48cf-ba3e-585b466835c1)

The following is the viz file for the RISC-V CPU Core.

![image](https://github.com/user-attachments/assets/b029d843-6d63-4f6f-886a-5b13c2f810d5)

## Pipelined Architecture for RISC-V CPU Core
The RISC-V core designed is divided into 5 pipeline stages. The following shows the pipelined stage for the RISC-V CPU Core.

``` tl-verilog

\m4_TLV_version 1d: tl-x.org
\SV
   // Template code can be found in: https://github.com/stevehoover/RISC-V_MYTH_Workshop
   
   m4_include_lib(['https://raw.githubusercontent.com/BalaDhinesh/RISC-V_MYTH_Workshop/master/tlv_lib/risc-v_shell_lib.tlv'])

\SV
   m4_makerchip_module   // (Expanded in Nav-TLV pane.)
\TLV

   // /====================\
   // | Sum 1 to 9 Program |
   // \====================/
   //
   // Add 1,2,3,...,9 (in that order).
   //
   // Regs:
   //  r10 (a0): In: 0, Out: final sum
   //  r12 (a2): 10
   //  r13 (a3): 1..10
   //  r14 (a4): Sum
   // 
   // External to function:
   m4_asm(ADD, r10, r0, r0)             // Initialize r10 (a0) to 0.
   // Function:
   m4_asm(ADD, r14, r10, r0)            // Initialize sum register a4 with 0x0
   m4_asm(ADDI, r12, r10, 1011)         // Store count of 10 in register a2.
   m4_asm(ADD, r13, r10, r0)            // Initialize intermediate sum register a3 with 0
   // Loop:
   m4_asm(ADD, r14, r13, r14)           // Incremental addition
   m4_asm(ADDI, r13, r13, 1)            // Increment intermediate register by 1
   m4_asm(BLT, r13, r12, 1111111111000) // If a3 is less than a2, branch to label named <loop>
   m4_asm(ADD, r10, r14, r0)            // Store final result to register a0 so that it can be read by main program
   m4_asm(SW, r0, r10, 10000)           // Store r10 result in dmem
   m4_asm(LW, r17, r0, 10000)           // Load contents of dmem to r17
   m4_asm(JAL, r7, 00000000000000000000) // Done. Jump to itself (infinite loop). (Up to 20-bit signed immediate plus implicit 0 bit (unlike JALR) provides byte address; last immediate bit should also be 0)
   m4_define_hier(['M4_IMEM'], M4_NUM_INSTRS)

   |cpu
      @0
         $reset = *reset;
         $clk_chi = *clk;
         
         //PC fetch - branch, jumps and loads introduce 2 cycle bubbles in this pipeline
         $pc[31:0] = >>1$reset ? '0 : (>>3$valid_taken_br ? >>3$br_tgt_pc :
                                       >>3$valid_load     ? >>3$inc_pc[31:0] :
                                       >>3$jal_valid      ? >>3$br_tgt_pc :
                                       >>3$jalr_valid     ? >>3$jalr_tgt_pc :
                                                     (>>1$inc_pc[31:0]));
         // Access instruction memory using PC
         $imem_rd_en = ~ $reset;
         $imem_rd_addr[31:0] = $pc[M4_IMEM_INDEX_CNT+1:2];
         
         
      @1
         //Getting instruction from IMem
         $instr[31:0] = $imem_rd_data[31:0];
         
         //Increment PC
         $inc_pc[31:0] = $pc[31:0] + 32'h4;
         
         //Decoding I,R,S,U,B,J type of instructions based on opcode [6:0]
         //Only [6:2] is used here because this implementation is for RV64I which does not use [1:0]
         $is_i_instr = $instr[6:2] ==? 5'b0000x ||
                       $instr[6:2] ==? 5'b001x0 ||
                       $instr[6:2] == 5'b11001;
         
         $is_r_instr = $instr[6:2] == 5'b01011 ||
                       $instr[6:2] ==? 5'b011x0 ||
                       $instr[6:2] == 5'b10100;
         
         $is_s_instr = $instr[6:2] ==? 5'b0100x;
         
         $is_u_instr = $instr[6:2] ==? 5'b0x101;
         
         $is_b_instr = $instr[6:2] == 5'b11000;
         
         $is_j_instr = $instr[6:2] == 5'b11011;
         
         //Immediate value decode
         $imm[31:0] = $is_i_instr ? { {21{$instr[31]}} , $instr[30:20]} :
                      $is_s_instr ? { {21{$instr[31]}} , $instr[30:25] , $instr[11:8] , $instr[7]} :
                      $is_b_instr ? { {20{$instr[31]}} , $instr[7] , $instr[30:25] , $instr[11:8] , 1'b0} :
                      $is_u_instr ? { $instr[31] , $instr[30:12] , { 12{1'b0}} } :
                      $is_j_instr ? { {12{$instr[31]}} , $instr[19:12] , $instr[20] , $instr[30:21] , 1'b0} :
                      >>1$imm[31:0];
         
         //Generate valid signals for each instruction fields
         $rs1_or_funct3_valid    = $is_r_instr || $is_i_instr || $is_s_instr || $is_b_instr;
         $rs2_valid              = $is_r_instr || $is_s_instr || $is_b_instr;
         $rd_valid               = $is_r_instr || $is_i_instr || $is_u_instr || $is_j_instr;
         $funct7_valid           = $is_r_instr;
         
         //Decode other fields of instruction - source and destination registers, funct, opcode
         ?$rs1_or_funct3_valid
            $rs1[4:0]    = $instr[19:15];
            $funct3[2:0] = $instr[14:12];
         
         ?$rs2_valid
            $rs2[4:0]    = $instr[24:20];
         
         ?$rd_valid
            $rd[4:0]     = $instr[11:7];
         
         ?$funct7_valid
            $funct7[6:0] = $instr[31:25];
         
         $opcode[6:0] = $instr[6:0];
         
         //Decode instruction in subset of base instruction set based on RISC-V 32I
         $dec_bits[10:0] = {$funct7[5],$funct3,$opcode};
         
         //Branch instructions
         $is_beq   = $dec_bits ==? 11'bx_000_1100011;
         $is_bne   = $dec_bits ==? 11'bx_001_1100011;
         $is_blt   = $dec_bits ==? 11'bx_100_1100011;
         $is_bge   = $dec_bits ==? 11'bx_101_1100011;
         $is_bltu  = $dec_bits ==? 11'bx_110_1100011;
         $is_bgeu  = $dec_bits ==? 11'bx_111_1100011;
         
         //Jump instructions
         $is_auipc = $dec_bits ==? 11'bx_xxx_0010111;
         $is_jal   = $dec_bits ==? 11'bx_xxx_1101111;
         $is_jalr  = $dec_bits ==? 11'bx_000_1100111;
         
         //Arithmetic instructions
         $is_addi  = $dec_bits ==? 11'bx_000_0010011;
         $is_add   = $dec_bits ==? 11'b0_000_0110011;
         $is_lui   = $dec_bits ==? 11'bx_xxx_0110111;
         $is_slti  = $dec_bits ==? 11'bx_010_0010011;
         $is_sltiu = $dec_bits ==? 11'bx_011_0010011;
         $is_xori  = $dec_bits ==? 11'bx_100_0010011;
         $is_ori   = $dec_bits ==? 11'bx_110_0010011;
         $is_andi  = $dec_bits ==? 11'bx_111_0010011;
         $is_slli  = $dec_bits ==? 11'b0_001_0010011;
         $is_srli  = $dec_bits ==? 11'b0_101_0010011;
         $is_srai  = $dec_bits ==? 11'b1_101_0010011;
         $is_sub   = $dec_bits ==? 11'b1_000_0110011;
         $is_sll   = $dec_bits ==? 11'b0_001_0110011;
         $is_slt   = $dec_bits ==? 11'b0_010_0110011;
         $is_sltu  = $dec_bits ==? 11'b0_011_0110011;
         $is_xor   = $dec_bits ==? 11'b0_100_0110011;
         $is_srl   = $dec_bits ==? 11'b0_101_0110011;
         $is_sra   = $dec_bits ==? 11'b1_101_0110011;
         $is_or    = $dec_bits ==? 11'b0_110_0110011;
         $is_and   = $dec_bits ==? 11'b0_111_0110011;
         
         //Store instructions
         $is_sb    = $dec_bits ==? 11'bx_000_0100011;
         $is_sh    = $dec_bits ==? 11'bx_001_0100011;
         $is_sw    = $dec_bits ==? 11'bx_010_0100011;
         
         //Load instructions - support only 4 byte load
         $is_load  = $dec_bits ==? 11'bx_xxx_0000011;
         
         $is_jump = $is_jal || $is_jalr;
         
      @2
         //Get Source register values from reg file
         $rf_rd_en1 = $rs1_or_funct3_valid;
         $rf_rd_en2 = $rs2_valid;
         
         $rf_rd_index1[4:0] = $rs1[4:0];
         $rf_rd_index2[4:0] = $rs2[4:0];
         
         //Register file bypass logic - data forwarding from ALU to resolve RAW dependence
         $src1_value[31:0] = $rs1_bypass ? >>1$result[31:0] : $rf_rd_data1[31:0];
         $src2_value[31:0] = $rs2_bypass ? >>1$result[31:0] : $rf_rd_data2[31:0];
         
         //Branch target PC computation for branches and JAL
         $br_tgt_pc[31:0] = $imm[31:0] + $pc[31:0];
         
         $rs1_bypass = >>1$rf_wr_en && (>>1$rd == $rs1);
         $rs2_bypass = >>1$rf_wr_en && (>>1$rd == $rs2);
         
      @3
         //ALU implementation
         $result[31:0] = $is_addi  ? $src1_value +  $imm :
                         $is_add   ? $src1_value +  $src2_value :
                         $is_andi  ? $src1_value &  $imm :
                         $is_ori   ? $src1_value |  $imm :
                         $is_xori  ? $src1_value ^  $imm :
                         $is_slli  ? $src1_value << $imm[5:0]:
                         $is_srli  ? $src1_value >> $imm[5:0]:
                         $is_and   ? $src1_value &  $src2_value:
                         $is_or    ? $src1_value |  $src2_value:
                         $is_xor   ? $src1_value ^  $src2_value:
                         $is_sub   ? $src1_value -  $src2_value:
                         $is_sll   ? $src1_value << $src2_value:
                         $is_srl   ? $src1_value >> $src2_value:
                         $is_sltu  ? $sltu_rslt[31:0]:
                         $is_sltiu ? $sltiu_rslt[31:0]:
                         $is_lui   ? {$imm[31:12], 12'b0}:
                         $is_auipc ? $pc + $imm:
                         $is_jal   ? $pc + 4:
                         $is_jalr  ? $pc + 4:
                         $is_srai  ? ({ {32{$src1_value[31]}} , $src1_value} >> $imm[4:0]) :
                         $is_slt   ? (($src1_value[31] == $src2_value[31]) ? $sltu_rslt : {31'b0, $src1_value[31]}):
                         $is_slti  ? (($src1_value[31] == $imm[31]) ? $sltiu_rslt : {31'b0, $src1_value[31]}) :
                         $is_sra   ? ({ {32{$src1_value[31]}}, $src1_value} >> $src2_value[4:0]) :
                         $is_load  ? $src1_value +  $imm :
                         $is_s_instr ? $src1_value + $imm :
                                    32'bx;
         
         $sltu_rslt[31:0]  = $src1_value <  $src2_value;
         $sltiu_rslt[31:0] = $src1_value <  $imm;
         
         //Jump instruction target PC computation
         $jalr_tgt_pc[31:0] = $imm[31:0] + $src1_value[31:0]; 
         
         //Branch equations
         $taken_br = $is_beq ? ($src1_value == $src2_value) :
                     $is_bne ? ($src1_value != $src2_value) :
                     $is_blt ? (($src1_value < $src2_value) ^ ($src1_value[31] != $src2_value[31])) :
                     $is_bge ? (($src1_value >= $src2_value) ^ ($src1_value[31] != $src2_value[31])) :
                     $is_bltu ? ($src1_value < $src2_value) :
                     $is_bgeu ? ($src1_value >= $src2_value) :
                     1'b0;
         
         $valid = ~(>>1$valid_taken_br || >>2$valid_taken_br || >>1$is_load || >>2$is_load || >>2$jump_valid || >>1$jump_valid);
         
         //Current instruction is valid & is a taken branch
         $valid_taken_br = $valid && $taken_br;
         
         //Current instruction is valid & is a load
         $valid_load = $valid && $is_load;
         
         //Current instruction is valid & is jump
         $jump_valid = $valid && $is_jump;
         $jal_valid  = $valid && $is_jal;
         $jalr_valid = $valid && $is_jalr;
         
         //Destination register update - ALU result or load result depending on instruction
         $rf_wr_en = (($rd != '0) && $rd_valid && $valid) || >>2$valid_load;
         $rf_wr_index[4:0] = $valid ? $rd[4:0] : >>2$rd[4:0];
         $rf_wr_data[31:0] = $valid ? $result[31:0] : >>2$ld_data[31:0];
         
      @4
         //Data memory access for load, store
         $dmem_addr[3:0]     =  $result[5:2];
         $dmem_wr_en         =  $valid && $is_s_instr;
         $dmem_wr_data[31:0] =  $src2_value[31:0];
         $dmem_rd_en         =  $valid_load;
         
         //Write back data read from load instruction to register
         $ld_data[31:0]      =  $dmem_rd_data[31:0];
         
      
   *passed = |cpu/xreg[14]>>10$value == (1+2+3+4+5+6+7+8+9+10);
   //Run for 80 cycles without any checks
   *passed = *cyc_cnt > 80;
   *failed = 1'b0;
   
   // Macro instantiations for:
   //  o instruction memory
   //  o register file
   //  o data memory
   //  o CPU visualization
   |cpu
      m4+imem(@1)    // Args: (read stage)
      m4+rf(@2, @3)  // Args: (read stage, write stage) - if equal, no register bypass is required
      m4+dmem(@4)    // Args: (read/write stage)
   
   m4+cpu_viz(@4)    // For visualisation, argument should be at least equal to the last stage of CPU logic
                       // @4 would work for all labs
\SV
   endmodule

```

 ### Load/Store Instructions
 Load/store and jump support is added along with the following two extra lines of code to test load and store.

![image](https://github.com/user-attachments/assets/0dca45bf-a90c-47be-8dcd-2566e2c65ff3)


###  Testing the core with a Testbench
With the implementation now complete, a simple testbench statement can be added to verify the functionality of the core. The "passed" and "failed" signals are used to communicate with the Makerchip platform to manage the simulation process. These signals indicate whether the simulation has passed without errors or has failed, in which case the errors can be identified through the log files. If the simulation fails, the "failed" signal instructs the platform to stop the simulation.

```tl-verilog
*passed = |cpu/xreg[10]>>5$value == (1+2+3+4+5+6+7+8+9);
```

Here, in the instruction memory, register r10 has been used to store the sum value. The simulation passed message can be seen under the "Log" tab. We have used ">>5" (ahead by 5) operator, because instead of stopping the simulator immediately, we wait for a couple of more cycles so as to see a little bit more on the waveform.

Simulation passed message is shown in the log.

![image](https://github.com/user-attachments/assets/076ac2ae-8268-4f60-89df-ca6cb76d6de1)


The sum of numbers from 1 to 9 is 45(i.e 2D in hex) which is verified in the waveform for |cpu/xreg[14] in the above figure

![3](https://github.com/user-attachments/assets/2b40e4bd-609f-48d6-8574-599703415085)


### Final RISC-V CPU Core Implementation

The block diagram of the final pipelined and the code is shown below.

![2](https://github.com/user-attachments/assets/9a3b67b4-8742-46e8-a4ba-f5533d06e3c1)
<img width="396" alt="1" src="https://github.com/user-attachments/assets/e8b7a357-95ed-4942-a7ab-e514361cf0b7">


## ASSIGNMENT 6

The RISC-V processor was initially designed using TL-Verilog in the Makerchip IDE. To deploy this design on an FPGA, it must first be converted to standard Verilog. This conversion was achieved using the Sandpiper-SaaS compiler. Following the conversion, pre-synthesis simulations will be conducted using the GTKWave simulator to verify the design.
### Step-by-Step Procedure:

1. Install pyyaml sandpiper simulation tools in the python virtual environment:
```bash
sudo apt-get install python3-venv
python3 -m venv .venv
source ~/.venv/bin/activate
pip3 install pyyaml click sandpiper-saas
```

2. Clone the VSDBabySoC design files and testbench.
```bash
git clone https://github.com/manili/VSDBabySoC.git
cd VSDBabySoc
```

![Screenshot from 2024-08-27 00-13-57](https://github.com/user-attachments/assets/875ca658-23d7-4d92-b301-a5f45e61a160)


3. Write your rvmyth file:
```bash
cd src/module
gedit rvmyth.tlv
```

![Screenshot from 2024-08-27 00-19-22](https://github.com/user-attachments/assets/63372e2a-9bd9-47b2-aefb-adcffe4a4066)


```tl-verilog
\m4_TLV_version 1d: tl-x.org
\SV
   m4_include_lib(['https://raw.githubusercontent.com/shivanishah269/risc-v-core/master/FPGA_Implementation/riscv_shell_lib.tlv'])
   
   // Module interface, either for Makerchip, or not.
   m4_ifelse_block(M4_MAKERCHIP, 1, ['
   // Makerchip module interface.
   m4_makerchip_module
   wire CLK = clk;
   logic [9:0] OUT;
   assign passed = cyc_cnt > 300;
   '], ['
   // Custom module interface for BabySoC.
   module rvmyth(
      output reg [9:0] OUT,
      input CLK,
      input reset
   );
   wire clk = CLK;
   '])
   
\TLV
   // External to function:
   m4_asm(ADD, r10, r0, r0)             // Initialize r10 (a0) to 0.
   // Function:
   m4_asm(ADD, r14, r10, r0)            // Initialize sum register a4 with 0x0
   m4_asm(ADDI, r12, r10, 1010)         // Store count of 10 in register a2.
   m4_asm(ADD, r13, r10, r0)            // Initialize intermediate sum register a3 with 0
   // Loop:
   m4_asm(ADD, r14, r13, r14)           // Incremental addition
   m4_asm(ADDI, r13, r13, 1)            // Increment intermediate register by 1
   m4_asm(BLT, r13, r12, 1111111111000) // If a3 is less than a2, branch to label named <loop>
   m4_asm(ADD, r10, r14, r0)            // Store final result to register a0 so that it can be read by main program
   m4_asm(SW, r0, r10, 10000)           // Store the final result value to byte address 16
   m4_asm(LW, r17, r0, 10000)           // Load the final result value from adress 16 to x17
   //
   m4_define_hier(['M4_IMEM'], M4_NUM_INSTRS)
   //
   |cpu
      @0
         $reset = *reset;
         $clk_chi = *clk;
         `BOGUS_USE($clk_chi)
      //Fetch
         // Next PC
         $pc[31:0] = (>>1$reset) ? 32'd0 : 
                     (>>3$valid_taken_br) ? >>3$br_tgt_pc : 
                     (>>3$valid_load) ? >>3$inc_pc : 
                     (>>3$valid_jump && >>3$is_jal) ? >>3$br_tgt_pc :
                     (>>3$valid_jump && >>3$is_jalr) ? >>3$jalr_tgt_pc : >>1$inc_pc;
         
         $imem_rd_en = !$reset;
         $imem_rd_addr[31:0] = $pc[M4_IMEM_INDEX_CNT+1:2];
         
      @1         
         $instr[31:0] = $imem_rd_data[31:0];
         $inc_pc[31:0] = $pc + 32'd4;          
      // Decode   
         $is_i_instr = $instr[6:2] == 5'b00000 ||
                       $instr[6:2] == 5'b00001 ||
                       $instr[6:2] == 5'b00100 ||
                       $instr[6:2] == 5'b00110 ||
                       $instr[6:2] == 5'b11001;
         $is_r_instr = $instr[6:2] == 5'b01011 ||
                       $instr[6:2] == 5'b10100 ||
                       $instr[6:2] == 5'b01100 ||
                       $instr[6:2] == 5'b01101;                       
         $is_b_instr = $instr[6:2] == 5'b11000;
         $is_u_instr = $instr[6:2] == 5'b00101 ||
                       $instr[6:2] == 5'b01101;
         $is_s_instr = $instr[6:2] == 5'b01000 ||
                       $instr[6:2] == 5'b01001;
         $is_j_instr = $instr[6:2] == 5'b11011;
         
         $imm[31:0] = $is_i_instr ? { {21{$instr[31]}} , $instr[30:20] } :
                      $is_s_instr ? { {21{$instr[31]}} , $instr[30:25] , $instr[11:8] , $instr[7] } :
                      $is_b_instr ? { {20{$instr[31]}} , $instr[7] , $instr[30:25] , $instr[11:8] , 1'b0} :
                      $is_u_instr ? { $instr[31:12] , 12'b0} : 
                      $is_j_instr ? { {12{$instr[31]}} , $instr[19:12] , $instr[20] , $instr[30:21] , 1'b0} : 32'b0;
         
         $rs2_valid = $is_r_instr || $is_s_instr || $is_b_instr;
         $rs1_valid = $is_r_instr || $is_s_instr || $is_b_instr || $is_i_instr;
         $rd_valid = $is_r_instr || $is_i_instr || $is_u_instr || $is_j_instr;
         $funct3_valid = $is_r_instr || $is_s_instr || $is_b_instr || $is_i_instr;
         $funct7_valid = $is_r_instr;
         
         ?$rs2_valid
            $rs2[4:0] = $instr[24:20];
         ?$rs1_valid
            $rs1[4:0] = $instr[19:15];
         ?$rd_valid
            $rd[4:0] = $instr[11:7];
         ?$funct3_valid
            $funct3[2:0] = $instr[14:12];
         ?$funct7_valid
            $funct7[6:0] = $instr[31:25];
            
         $opcode[6:0] = $instr[6:0];
         
         $dec_bits[10:0] = {$funct7[5],$funct3,$opcode};
         
         // Branch Instruction
         $is_beq = $dec_bits[9:0] == 10'b000_1100011;
         $is_bne = $dec_bits[9:0] == 10'b001_1100011;
         $is_blt = $dec_bits[9:0] == 10'b100_1100011;
         $is_bge = $dec_bits[9:0] == 10'b101_1100011;
         $is_bltu = $dec_bits[9:0] == 10'b110_1100011;
         $is_bgeu = $dec_bits[9:0] == 10'b111_1100011;
         
         // Arithmetic Instruction
         $is_add = $dec_bits == 11'b0_000_0110011;
         $is_addi = $dec_bits[9:0] == 10'b000_0010011;
         $is_or = $dec_bits == 11'b0_110_0110011;
         $is_ori = $dec_bits[9:0] == 10'b110_0010011;
         $is_xor = $dec_bits == 11'b0_100_0110011;
         $is_xori = $dec_bits[9:0] == 10'b100_0010011;
         $is_and = $dec_bits == 11'b0_111_0110011;
         $is_andi = $dec_bits[9:0] == 10'b111_0010011;
         $is_sub = $dec_bits == 11'b1_000_0110011;
         $is_slti = $dec_bits[9:0] == 10'b010_0010011;
         $is_sltiu = $dec_bits[9:0] == 10'b011_0010011;
         $is_slli = $dec_bits == 11'b0_001_0010011;
         $is_srli = $dec_bits == 11'b0_101_0010011;
         $is_srai = $dec_bits == 11'b1_101_0010011;
         $is_sll = $dec_bits == 11'b0_001_0110011;
         $is_slt = $dec_bits == 11'b0_010_0110011;
         $is_sltu = $dec_bits == 11'b0_011_0110011;
         $is_srl = $dec_bits == 11'b0_101_0110011;
         $is_sra = $dec_bits == 11'b1_101_0110011;
         
         // Load Instruction
         $is_load = $dec_bits[6:0] == 7'b0000011;
         
         // Store Instruction
         $is_sb = $dec_bits[9:0] == 10'b000_0100011;
         $is_sh = $dec_bits[9:0] == 10'b001_0100011;
         $is_sw = $dec_bits[9:0] == 10'b010_0100011;
         
         // Jump Instruction
         $is_lui = $dec_bits[6:0] == 7'b0110111;
         $is_auipc = $dec_bits[6:0] == 7'b0010111;
         $is_jal = $dec_bits[6:0] == 7'b1101111;
         $is_jalr = $dec_bits[9:0] == 10'b000_1100111;
         
         $is_jump = $is_jal || $is_jalr;
         
      @2   
      // Register File Read
         $rf_rd_en1 = $rs1_valid;
         ?$rf_rd_en1
            $rf_rd_index1[4:0] = $rs1[4:0];
         
         $rf_rd_en2 = $rs2_valid;
         ?$rf_rd_en2
            $rf_rd_index2[4:0] = $rs2[4:0];
            
      // Branch Target PC       
         $br_tgt_pc[31:0] = $pc + $imm;
      
      // Jump Target PC
         $jalr_tgt_pc[31:0] = $src1_value + $imm;
         
      // Input signals to ALU
         $src1_value[31:0] = ((>>1$rd == $rs1) && >>1$rf_wr_en) ? >>1$result : $rf_rd_data1[31:0];
         $src2_value[31:0] = ((>>1$rd == $rs2) && >>1$rf_wr_en) ? >>1$result : $rf_rd_data2[31:0];
         
      @3   
         
      // ALU
         $sltu_result = $src1_value < $src2_value ;
         $sltiu_result = $src1_value < $imm ;
         
         $result[31:0] = $is_addi ? $src1_value + $imm :
                         $is_add ? $src1_value + $src2_value : 
                         $is_or ? $src1_value | $src2_value : 
                         $is_ori ? $src1_value | $imm :
                         $is_xor ? $src1_value ^ $src2_value :
                         $is_xori ? $src1_value ^ $imm :
                         $is_and ? $src1_value & $src2_value :
                         $is_andi ? $src1_value & $imm :
                         $is_sub ? $src1_value - $src2_value :
                         $is_slti ? (($src1_value[31] == $imm[31]) ? $sltiu_result : {31'b0,$src1_value[31]}) :
                         $is_sltiu ? $sltiu_result :
                         $is_slli ? $src1_value << $imm[5:0] :
                         $is_srli ? $src1_value >> $imm[5:0] :
                         $is_srai ? ({{32{$src1_value[31]}}, $src1_value} >> $imm[4:0]) :
                         $is_sll ? $src1_value << $src2_value[4:0] :
                         $is_slt ? (($src1_value[31] == $src2_value[31]) ? $sltu_result : {31'b0,$src1_value[31]}) :
                         $is_sltu ? $sltu_result :
                         $is_srl ? $src1_value >> $src2_value[5:0] :
                         $is_sra ? ({{32{$src1_value[31]}}, $src1_value} >> $src2_value[4:0]) :
                         $is_lui ? ({$imm[31:12], 12'b0}) :
                         $is_auipc ? $pc + $imm :
                         $is_jal ? $pc + 4 :
                         $is_jalr ? $pc + 4 : 
                         ($is_load || $is_s_instr) ? $src1_value + $imm : 32'bx;
                         
      // Register File Write
         $rf_wr_en = ($rd_valid && $valid && $rd != 5'b0) || >>2$valid_load;
         ?$rf_wr_en
            $rf_wr_index[4:0] = !$valid ? >>2$rd[4:0] : $rd[4:0];
      
         $rf_wr_data[31:0] = !$valid ? >>2$ld_data[31:0] : $result[31:0];
      
      // Branch
         $taken_br = $is_beq ? ($src1_value == $src2_value) :
                     $is_bne ? ($src1_value != $src2_value) :
                     $is_blt ? (($src1_value < $src2_value) ^ ($src1_value[31] != $src2_value[31])) :
                     $is_bge ? (($src1_value >= $src2_value) ^ ($src1_value[31] != $src2_value[31])) :
                     $is_bltu ? ($src1_value < $src2_value) :
                     $is_bgeu ? ($src1_value >= $src2_value) : 1'b0;
                     
         $valid_taken_br = $valid && $taken_br;
         
      // Load
         $valid_load = $valid && $is_load;
         $valid = !(>>1$valid_taken_br || >>2$valid_taken_br || >>1$valid_load || >>2$valid_load || >>1$valid_jump || >>2$valid_jump);
      
      // Jump
         $valid_jump = $valid && $is_jump;
                  
      @4
         $dmem_rd_en = $valid_load;
         $dmem_wr_en = $valid && $is_s_instr;
         $dmem_addr[3:0] = $result[5:2];
         $dmem_wr_data[31:0] = $src2_value[31:0];
         
      @5   
         $ld_data[31:0] = $dmem_rd_data[31:0];
         
      // Note: Because of the magic we are using for visualisation, if visualisation is enabled below,
      //       be sure to avoid having unassigned signals (which you might be using for random inputs)
      //       other than those specifically expected in the labs. You'll get strange errors for these.

         `BOGUS_USE($is_beq $is_bne $is_blt $is_bge $is_bltu $is_bgeu)
         `BOGUS_USE($is_sb $is_sh $is_sw)
   // Assert these to end simulation (before Makerchip cycle limit).
   \SV_plus
      always @ (posedge CLK) begin
         *OUT = |cpu/xreg[14]>>5$value;                
      end
   
   // Macro instantiations for:
   //  o instruction memory
   //  o register file
   //  o data memory
   //  o CPU visualization
   |cpu
      m4+imem(@1)    // Args: (read stage)
      m4+rf(@2, @3)  // Args: (read stage, write stage) - if equal, no register bypass is required
      m4+dmem(@4)    // Args: (read/write stage)

     
\SV
   
   endmodule
```

4. Convert the .tlv to .v using the sandpiper tool converter:

```bash
sandpiper-saas -i ./src/module/*.tlv -o rvmyth.v --bestsv --noline -p verilog --outdir ./src/module/
```

![Screenshot from 2024-08-27 00-15-33](https://github.com/user-attachments/assets/ec061de6-e41e-4793-b2ef-d2c83e9d81bb)


5. Make the pre_synth_sim.vcd:
```bash
make pre_synth_sim
```

![Screenshot from 2024-08-27 00-15-54](https://github.com/user-attachments/assets/bb8699f2-9bc7-491c-baa5-a185be10968f)


6. Now compile and simulate RISC-V design file
To compile and simulate vsdbabysoc design. The result is tored in the output folder hence we will move to the output folder
The simulation will be done in gtkwave.

```bash
iverilog -o output/pre_synth_sim.out -DPRE_SYNTH_SIM src/module/testbench.v -I src/include -I src/module
cd output
./pre_synth_sim.out
gtkwave pre_synth_sim.vcd
```

![Screenshot from 2024-08-27 00-25-09](https://github.com/user-attachments/assets/bdc8d60f-5c07-4ec8-ae0e-2dfecc949708)


### Pre-synthesis Simulation Results:
We have to plot the following signals in gtkwave:

- clk_chi: The clock input to the RISC-V core.
- reset: The input reset signal to the RISC-V core.
- OUT[9:0]: The 10-bit output [9:0] OUT port of the RISC-V core i.e the reg[14].


### Makerchip platform waveforms for the .tlv file for comparison

![10](https://github.com/user-attachments/assets/6e065dfc-d8a1-4460-a6ee-8957f27d3862)

<img width="1358" alt="11" src="https://github.com/user-attachments/assets/73a266b2-da82-4db2-b307-9b8270409fbc">

![Screenshot from 2024-08-27 00-57-54](https://github.com/user-attachments/assets/f0d5f9f0-1a1e-4fe4-9cdd-47fa03396792)

We can see the sum from 0 to 9 stored in the reg[14] which shows 45 which is `Ox2D` in hexadecimal.

### Waveforms from GTKwave platform after simulating the .v file

![Screenshot from 2024-08-27 00-33-20](https://github.com/user-attachments/assets/9410bdba-5942-4513-b88e-bb9a4e93f788)


We can see the sum from 0 to 9 stored in the reg[14] which shows 45 which is `Ox2D` in hexadecimal.

The viz file is shown below showing the sum of 1 to 9 which is 45 stored in the r10.
![image](https://github.com/user-attachments/assets/25f652e1-cd11-437f-9fc3-ae17b81b9511)


## ASSIGNMENT 7

### VSDBabySoC:
The VSDBabySoC is a compact yet capable SoC based on the RISC-V architecture. It was designed primarily to test the integration of three open-source IP cores together for the first time and to fine-tune its analog components. The SoC includes an RVMYTH microprocessor, an 8x phase-locked loop (PLL) for generating a stable clock, and a 10-bit digital-to-analog converter (DAC) for communication with other analog devices.

### RVMYTH:
The RVMYTH core is a straightforward RISC-V-based CPU, first introduced in Lab 8 and Lab 9. In Lab 9, the RISC-V processor was built from the ground up using TLV (Transaction-Level Verilog) for quicker development. The primary function of this processor is to calculate the sum of numbers from 1 to 9 and produce the resulting sum as output.

![6](https://github.com/user-attachments/assets/1c705c38-8e33-470a-9c64-1ef539234e7f)


### BabySoC Simulation:
We will be implementing the 2 followings:
- Phase-Locked Loop (PLL)
- Digital-to-Analog Converter (DAC)

 #### Phase-Locked Loop (PLL):
 A Phase-Locked Loop (PLL) is an electronic system designed to synchronize the phase and frequency of an output signal with a reference signal. It typically consists of three key components: a Phase Detector, a Loop Filter, and a Voltage-Controlled Oscillator (VCO). The Phase Detector compares the phase of the reference signal with that of the output signal, generating an error signal that reflects their phase difference. This error signal is then smoothed by the Loop Filter, which reduces noise and enhances the system's stability. Finally, the VCO adjusts its output frequency in response to the filtered error signal, working to minimize the phase difference between the signals. PLLs are widely used in various applications, including clock generation, frequency synthesis, and data recovery in communication systems.
 #### Digital-to-Analog Converter (DAC):
A Digital-to-Analog Converter (DAC) is a device that transforms digital signals, usually in binary form, into analog signals like voltage or current. This conversion is crucial in systems where digital data needs to be understood by analog devices or for outputs that need to be experienced by humans, such as in audio and video equipment. DACs are commonly used in applications such as audio playback, video display, and signal processing.

### To perform Funtional Simulation
- After cloning the given repository for BabySoC, replace the rvymth.v file with our rvymth.v. Also modify the vsdbabysoc.v file with our clock. 
- Follow the steps for functional simulation.

```bash
cd BabySoC_Simulation
iverilog -o ./pre_synth_sim.out -DPRE_SYNTH_SIM src/module/testbench.v -I src/include -I src/module/
./pre_synth_sim.out
gtkwave pre_synth_sim.vcd
```

![Screenshot from 2024-09-03 00-04-50](https://github.com/user-attachments/assets/3cdeddb4-a819-4618-9243-754360f8a829)


![Screenshot from 2024-09-03 00-17-28](https://github.com/user-attachments/assets/5df76b4d-9451-4af9-b2f0-05bb141dc3f9)


![Screenshot from 2024-09-03 00-15-55](https://github.com/user-attachments/assets/6c58f306-8cc5-49a7-beaa-5b726d0c78fb)


We can observe the output of the sum for numbers 1 to 9 after simulation is graduallly increasing from 0x00 to 0x2D which is 0-45 in hexadecimal.

#### VCO_IN
- **Type**: Input
- **Description**: The input clock reference signal to the Phase-Locked Loop (PLL) module. The PLL uses this signal to generate a stable and synchronized output clock signal.

#### CLK
- **Type**: Output
- **Description**: The output clock signal generated by the PLL module. This is a stabilized version of the input clock signal (VCO_IN) and is used to drive various parts of the system.

#### CLK_chi
- **Type**: Output
- **Description**: The clock signal used by the RISC-V CPU for its operations. It is derived from the PLL's output clock (CLK) to ensure synchronized CPU operation.

#### RV_TO_DAC
- **Type**: Output
- **Description**: This output wire is connected to the Xreg[14] register of the RISC-V CPU's register file. It carries the digital data that will be converted into an analog signal by the DAC.

#### OUT
- **Type**: Output
- **Description**: The analog signal output from the DAC unit. This signal is the analog representation of the digital data received from the RV_TO_DAC wire.

#### reset
- **Type**: Input
- **Description**: The reset signal for the RISC-V CPU. When activated, it initializes or resets the CPU to a known state, ensuring a clean start for system operations.


**Hence the simulation successfully demonstrates the integration of DAC and PLL peripherals with the RISC-V processor, converting digital outputs to analog signals.**

</details>
<details>
<summary> Post-Midsem </summary>
<br>
  
# ASSIGNMENT 1 : RTL design using Verilog with SKY130 Technology
<details>
<summary>Day-1</summary>
<br>
  
## iVerilog based Simulation flow:
 
 ![image](https://github.com/user-attachments/assets/0e2f8052-f0f8-4cfa-bab0-fc83a490afb9)

**Task 1: Fetching the required files from github:**

**Commands:**
```
sudo apt-get install git
cd /home
mkdir VLSI
cd VLSI
git clone https://github.com/kunalg123/sky130RTLDesignAndSynthesisWorkshop.git
cd sky130RTLDesignAndSynthesisWorkshop/verilog_files
ls
```

**Screenshot of the terminal window:**

![Screenshot from 2024-10-21 21-16-23](https://github.com/user-attachments/assets/3e0efe2a-0d0b-4681-8aee-0c604dab340e)


**Task 2 : Running iVerilog gtkwave:**

 It is to implement a 2:1 multiplexer.

**Command to view Verilog code & testbench file:**
```
vim tb_good_mux.v -o good_mux.v
```
![Screenshot from 2024-10-21 21-19-09](https://github.com/user-attachments/assets/2dc987b8-b7ca-47d7-b177-4477b5860d49)


**Implementing the waveform on gtkwave:**
```
iverilog good_mux.v tb_good_mux.v
ls
./a.out
gtkwave tb_good_mux.vcd
```

**Screenshots of terminal window & gtkwave waveform:**

![Screenshot from 2024-10-21 21-26-52](https://github.com/user-attachments/assets/75305a40-7636-41a5-a4fd-abf255999caf)
![Screenshot from 2024-10-21 21-28-30](https://github.com/user-attachments/assets/25ca6a7d-a5ac-4d19-adbd-724318ed8695)
![Screenshot from 2024-10-21 21-28-40](https://github.com/user-attachments/assets/197238b7-3a2f-47a0-833d-037481f527c3)


**Task 3 : Synthesis of 2:1 Mux using Yosys and Logic Synthesis:**

## YOSYS:
A synthesizer is essential in digital design, converting RTL (Register Transfer Level) code into a gate-level netlist. This netlist gives a detailed representation of the circuit, including the logic gates and their connections, forming the groundwork for subsequent steps like placement and routing. In this particular design process, Yosys, an open-source synthesis tool for Verilog HDL, is being used. Yosys employs various optimization strategies to produce an efficient gate-level design from the RTL code.

The primary inputs and outputs are the same in both the RTL design and the synthesized netlist, allowing the same test bench to be used for both.

**Block Diagram of Yosys setup :**
![image](https://github.com/user-attachments/assets/adf3de9f-78c3-4ea8-b07d-01788b398b76)



**Block Diagram of Systhesis Verification :**
![image](https://github.com/user-attachments/assets/72e54532-7abc-43ac-b32e-6a5bde0a9014)

## Logic Synthesis:

**RTL Design:** The design is modeled using a behavioral description in Hardware Description Language (HDL) according to the given specifications.

**Synthesis:** The RTL code is transformed into a gate-level representation, where the design is mapped into logic gates and connections, producing a file called the netlist. In Verilog, a netlist is a representation of a circuit that describes how various components (such as logic gates, flip-flops, or modules) are interconnected. 

**Liberty(.lib):** Its a collection of logical modules. It includes basic logic gates like And, Or, Not, etc... and it contains different variants of the same gate ike 2input, 3input, 4input, slow, fast, medium gates etc. Fast cells are used if only high performance is needed. Slower cells is used to address hold time issues. IThe selection of faster cells in digital circuit design can increase area and power consumption while potentially leading to hold time violations. Conversely, excessive use of slower cells can result in suboptimal performance. The optimal cell selection for synthesis is guided by constraints that balance area, power, and timing requirements.

### Command steps for Yosys:

**This will invoke/start the yosys:**
```
yosys
```


**Load the sky130 standard library and Synthesize:**
```
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib      
read_verilog good_mux.v
synth -top good_mux
```

![Screenshot from 2024-10-21 21-41-10](https://github.com/user-attachments/assets/14aa0ea0-63b1-48c8-99ef-d4e44068d0ef)


**Map to the standard library:**
```
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
```

![Screenshot from 2024-10-21 21-40-58](https://github.com/user-attachments/assets/6b8b1de0-3682-4dc7-80c0-61e611bf7005)


**View the graphical representation of the generated logic**
```
show
```
![Screenshot from 2024-10-21 21-38-31](https://github.com/user-attachments/assets/53ed05c3-bb2d-4a0b-b68c-5c28d3e7b533)



**Save the netlist, using the write_verilog command:**
```
write_verilog -noattr good_mux_netlist.v
cat good_mux_netlist.v
```
![Screenshot from 2024-10-21 21-47-55](https://github.com/user-attachments/assets/cd394077-7483-4d7c-b713-ebaec6952bba)


</details>

<details>
<summary>Day-2</summary>
<br>
	
## Timing, Hierarchical v/s Flat Synthesis and Flip-Flop Coding:

### Task 1:

Run the below commands to view the contents inside the .lib file:

```
cd ASIC/sky130RTLDesignAndSynthesisWorkshop/lib/
vim sky130_fd_sc_hd__tt_025C_1v80.lib
```
![Screenshot from 2024-10-21 21-58-05](https://github.com/user-attachments/assets/049234b0-b9b4-4482-846f-4532f3accc22)



The liberty(.lib) files store PVT parameters (Process, Voltage, Temperature). Variations in these parameters can significantly affect circuit performance. Manufacturing variations, voltage fluctuations, and temperature changes all contribute to this impact."

We can also find different versions of the same cell. For example, consider the AND gate

![Screenshot from 2024-10-21 22-03-06](https://github.com/user-attachments/assets/f509b132-f99e-4ed1-ac4c-9046260a7cee)
![Screenshot from 2024-10-21 22-02-56](https://github.com/user-attachments/assets/f3cfa56a-7959-4045-beac-567eccf21def)
![Screenshot from 2024-10-21 22-02-41](https://github.com/user-attachments/assets/3ea931f1-1e20-417b-920f-ba3ea7676975)
![Screenshot from 2024-10-21 22-02-29](https://github.com/user-attachments/assets/50ea4fd7-40da-44fe-88a6-ee314d42573f)


We can observe that:

* and2_0 -- taking the least area, more delay and low power.
* and2_1 -- taking more area, less delay and high power.
* and2_2 -- taking the largest area, larger delay and highest power.

### Task 2: Hierarchical vs Flat Synthesis

Hierarchical synthesis involves synthesizing a complex design by breaking it down into various sub-modules, where each module is synthesized separately to generate gate-level netlists and then integrated. Hierarchical synthesis allows for better organization, reuse of modules, and incremental changes to the design without affecting the entire system. Flat synthesis, on the other hand, treats the entire design as a single, monolithic unit during the synthesis process and regardless of any hierarchical relations, it is synthesized into a single netlist. Flat synthesis can be useful for optimizing certain designs but it becomes challenging to maintain, analyze, and modify the design due to its lack of structural modularity.

Consider the verilog file `multiple_modules.v` which is given in the verilog_files directory

```
module sub_module2 (input a, input b, output y);
    assign y = a | b;
endmodule

module sub_module1 (input a, input b, output y);
    assign y = a&b;
endmodule


module multiple_modules (input a, input b, input c , output y);
    wire net1;
    sub_module1 u1(.a(a),.b(b),.y(net1));  //net1 = a&b
    sub_module2 u2(.a(net1),.b(c),.y(y));  //y = net1|c ,ie y = a&b + c;
endmodule
```

To perform **hierarchical synthesis** on the `multiple_modules.v` file type the following commands:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog multiple_modules.v
synth -top multiple_modules
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show multiple_modules
write_verilog -noattr multiple_modules_hier.v
```

The following statistics are displayed:
![Screenshot from 2024-10-21 22-05-41](https://github.com/user-attachments/assets/474d2620-3712-42d1-90f1-6781c3443300)


Netlist:
![Screenshot from 2024-10-21 22-06-10](https://github.com/user-attachments/assets/5c699ef0-1141-473f-ba6d-c5c5139f87e6)


Hierarchical netlist code:
![Screenshot from 2024-10-21 22-07-52](https://github.com/user-attachments/assets/34d899ef-41f6-47ae-9e27-519fe39cefff)



To perform **flat synthesis** on the `multiple_modules.v` file type the following commands:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog multiple_modules.v
synth -top multiple_modules
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
flatten
show
write_verilog -noattr multiple_modules_flat.v
```

The following statistics are displayed:

![Screenshot from 2024-10-21 22-09-31](https://github.com/user-attachments/assets/80d5bf64-f9ce-44dd-8847-640fbe4d9a09)


Netlist:
![Screenshot from 2024-10-21 22-15-47](https://github.com/user-attachments/assets/145e7971-ba4b-4eab-ac89-40187bd0dd53)



Flat synthesis netlist code:
![Screenshot from 2024-10-21 22-17-09](https://github.com/user-attachments/assets/3342eadd-24ca-452f-9a8e-2f5c6ad3cc3a)


To perform **sub module synthesis**. type the below commands:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
read_verilog multiple_modules.v 
synth -top sub_module
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
show
```

The following statistics are displayed:

![Screenshot from 2024-10-21 22-22-56](https://github.com/user-attachments/assets/e0ae3433-61b1-4938-a087-dfa83d25e81b)


Netlist:

![Screenshot from 2024-10-21 22-23-24](https://github.com/user-attachments/assets/bc03775a-28e6-478b-a900-7681136c6b7b)

### Task 3

**Flip-Flop Coding Styles and Optimizations**

In a digital design, when an input signal changes state, the output changes after a propogation delay. All logic gates add some delay to singals. These delays cause expected and unwanted transitions in the output, called as Glitches where the output value is momentarily different from the expected value. An increased delay in one path can cause glitch when those signals are combined at the output gate. In short, more combinational circuits lead to more glitchy outputs that will not settle down with the output value.

A D flip-flop is a sequential element that follows the input pin d at the clock's given edge. D flip-flop is a fundamental component in digital logic circuits. There are two types of D Flip-Flops being implemented: Rising-Edge D Flip Flop and Falling-Edge D Flip Flop.
Every flop element needs an initial state, else the combinational circuit will evaluate to a garbage value. In order to achieve this, there are control pins in the flop namely: Set and Reset which can either be Synchronous or Asynchronous.
**Asynchronous Reset Flip-flop:**

Here, always block gets evaluated when there is a change in the clock or change in the set/reset.The circuit is sensitive to positive edge of the clock. Upon the signal going low/high depending on reset or set control, singal q line goes changes respectively. Hence, it does not wait for the positive edge of the clock and happens irrespective of the clock_.

![Screenshot from 2024-10-21 22-29-27](https://github.com/user-attachments/assets/0351bb23-4e22-4701-b370-2e149492963f)

Run the below code to view the simulation:

```
iverilog dff_asyncres.v tb_dff_asyncres.v
./a.out
gtkwave tb_dff_asyncres.vcd
```

Waveform:
![Screenshot from 2024-10-21 22-30-33](https://github.com/user-attachments/assets/a09539fa-d917-4aa5-9ac7-75160d556918)



Run the below code to view the netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_asyncres.v
synth -top dff_asyncres
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
```
![Screenshot from 2024-10-21 22-31-26](https://github.com/user-attachments/assets/50706975-54c7-452c-b43f-e595afaed156)

![Screenshot from 2024-10-21 22-32-01](https://github.com/user-attachments/assets/a9b0d1b1-fb14-4273-9d5b-bee7c00cf04c)


**Synchronous Reset Flip-flop:**

Verilog Code:

```
module dff_syncres ( input clk , input async_reset , input sync_reset , input d , output reg q );
always @ (posedge clk )
begin
	if (sync_reset)
		q <= 1'b0;
	else	
		q <= d;
end
endmodule
```

Run the below code to view the simulation:

```
iverilog dff_syncres.v tb_dff_syncres.v
./a.out
gtkwave tb_dff_syncres.vcd
```

Waveform:

![Screenshot from 2024-10-21 22-37-59](https://github.com/user-attachments/assets/a592fb77-be4e-4974-b05e-92ee0491b498)


Run the below code to view the netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_syncres.v
synth -top dff_syncres
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
```
![Screenshot from 2024-10-21 22-38-34](https://github.com/user-attachments/assets/a1cdc8f3-1b91-4f0f-b9dd-7e7a8e1130a2)
![Screenshot from 2024-10-21 22-38-58](https://github.com/user-attachments/assets/42b3d172-6104-483b-9deb-81a59b9e65ca)


**Asynchronous Set Flip-flop:**

Verilog Code:

```
module dff_async_set ( input clk ,  input async_set , input d , output reg q );
always @ (posedge clk , posedge async_set)
begin
	if(async_set)
		q <= 1'b1;
	else	
		q <= d;
end
endmodule
```

Run the below code to view the simulation:

```
iverilog dff_async_set.v tb_dff_async_set.v
./a.out
gtkwave tb_dff_async_set.vcd
```

Waveform:

![Screenshot from 2024-10-21 22-41-25](https://github.com/user-attachments/assets/fc39938b-831d-4ee6-a31a-761c040bf139)


Run the below code to view the netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_async_set.v
synth -top dff_async_set
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
```
![Screenshot from 2024-10-21 22-43-44](https://github.com/user-attachments/assets/ca1f64eb-f438-4511-bbe5-f29ba939b7d5)

![Screenshot from 2024-10-21 22-44-44](https://github.com/user-attachments/assets/329deecf-e155-4c18-9689-ccca36097aa6)


### Task 4: Optimizations

Example 1:

![Screenshot from 2024-10-21 22-48-40](https://github.com/user-attachments/assets/7603c264-5b28-4b1a-9cdb-3f9566b08844)



Run the below code to view the netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog mult_2.v
synth -top mul2
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr mult_2_net.v
```

Statistics:
![Screenshot from 2024-10-21 22-50-06](https://github.com/user-attachments/assets/943905e5-333a-4b94-9783-ff60607836c2)


Netlist:

![Screenshot from 2024-10-21 22-50-29](https://github.com/user-attachments/assets/8f3c3290-5144-4d6b-9b5c-9edaec8e076f)


Netlist code:

![Screenshot from 2024-10-21 22-51-20](https://github.com/user-attachments/assets/060fbf4a-f50e-493a-96b9-5b40efb1a98d)

Example 2:

Consider the verilog code 'mult_8.v' :

![Screenshot from 2024-10-21 22-53-50](https://github.com/user-attachments/assets/1c50c8ba-3d65-41d2-8792-3117c830bd4e)
 
Run the following commands:
```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog mult_8.v
synth -top mult8
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr mult_8_net.v
```

Statistics:

![Screenshot from 2024-10-21 22-54-59](https://github.com/user-attachments/assets/8301d3f6-5be1-4567-b95d-3e5ed1d0540c)


Netlist:

![Screenshot from 2024-10-21 22-55-32](https://github.com/user-attachments/assets/6c0ff909-c3a7-4bd7-89af-300b40365ae7)


Netlist code:
![Screenshot from 2024-10-21 22-55-57](https://github.com/user-attachments/assets/5dc579c7-4a21-4dee-8fa9-f973371e2082)


</details>
<details>
<summary>Day-3</summary>
<br>
##  Combinational and sequential optimizations
	
 There are two types of optimisations: Combinational and Sequential optimisations. These optimisations are done inorder to achieve designs that are efficient in terms of area, power, and performance.

### Task 1: Combinational Optimization

The techiniques used are: Constant Propagation (Direct Optimisation) & Boolean Logic Optimisation (using K-Map or Quine McCluskey method)

**Constant Propagation:**

Consider the below circuit:

![image](https://github.com/user-attachments/assets/24fcec7b-7b46-4d73-b93d-a257883ef6e5)

The top circuit uses 6 transistors(3 nmos and 3 pmos). The bottom cicuit uses 2 transistors(1 nmos and 1 pmos) when we make A zero as the logic becomes invertor. 

**Boolean Logic Optimisation:**

Consider the below verilog code:

`assign y = a?(b?c:(c?a:0)):(!c);`

The ternary operator (?:) will realize a mux upon synthesis as shown below. 

![image](https://github.com/user-attachments/assets/22937fd8-8b2e-4da1-a19a-25563b92f5dd)

The circuit can be optimised as follows:

![image](https://github.com/user-attachments/assets/45a4b461-cc9b-4512-a0d1-7ecd123e09bf)

**Example 1:**

Verllog code:

```
module opt_check (input a , input b , output y);
	assign y = a?b:0;
endmodule
```

The above code infers a multiplexer and since one of the inputs of the multiplexer is always connected to the ground it will infer an AND gate on optimisation.

Run the below code for netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog opt_check.v
synth -top opt_check
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr opt_check_net.v
```

![image](https://github.com/user-attachments/assets/76a0d332-a8e3-400c-b388-f0488e095723)

![image](https://github.com/user-attachments/assets/a691c891-a859-490a-bf36-e2df96a0e048)

**Example 2:**

Verllog code:

```
module opt_check2 (input a , input b , output y);
	assign y = a?1:b;
endmodule
```

Since one of the inputs of the multiplexer is always connected to the logic 1 it will infer an OR gate on optimisation.The OR gate will be NAND implementation since NOR gate has stacked pmos while NAND implementation has stacked nmos.

Run the below code for netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog opt_check2.v
synth -top opt_check2
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr opt_check2_net.v
```

![image](https://github.com/user-attachments/assets/d8b15a35-fda7-42ab-aa0c-1283f1901dbe)
![image](https://github.com/user-attachments/assets/207283c3-a667-4bfe-8b4a-0934c2a0e41a)

**Example 3:**

Verilog code:

```
module opt_check3 (input a , input b, input c , output y);
	assign y = a?(c?b:0):0;
endmodule
```

On optimisation the above design becomes a 3 input AND gate.

Run the below code for netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog opt_check3.v
synth -top opt_check3
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr opt_check3_net.v
```

![image](https://github.com/user-attachments/assets/bff79804-383e-4a5c-befd-a49bf8894a0f)

![image](https://github.com/user-attachments/assets/9b852b8b-031e-43b4-a823-10a4557ae2a1)

**Example 4:**

Verilog code:

```
module opt_check4 (input a , input b, input c , output y);
	assign y = a?(c?b:0):0;
endmodule
```

On optimisation the above design becomes a 2 input XNOR gate.

Run the below code for netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog opt_check4.v
synth -top opt_check4
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr opt_check4_net.v
```
![image](https://github.com/user-attachments/assets/948dda7b-a8ea-4917-9aa7-8b740747d8e1)

![image](https://github.com/user-attachments/assets/d6bf7230-3e44-4fed-ac14-f91385bbc03b)


**Example 5:**

Verilog code:

```
module sub_module1(input a , input b , output y);
 assign y = a & b;
endmodule

module sub_module2(input a , input b , output y);
 assign y = a^b;
endmodule

module multiple_module_opt(input a , input b , input c , input d , output y);
wire n1,n2,n3;

sub_module1 U1 (.a(a) , .b(1'b1) , .y(n1));
sub_module2 U2 (.a(n1), .b(1'b0) , .y(n2));
sub_module2 U3 (.a(b), .b(d) , .y(n3));

assign y = c | (b & n1); 

endmodule
```

On optimisation the above design becomes a AND OR gate

Run the below code for netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog multiple_module_opt.v
synth -top multiple_module_opt
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
flatten
show
write_verilog -noattr multiple_module_opt_net.v
```

![image](https://github.com/user-attachments/assets/372b9d74-1482-46ff-811d-4ab633a2b2b3)
![image](https://github.com/user-attachments/assets/c33a4b7c-1677-4178-8fe0-152f3d619c7d)


**Example 6:**

Verilog code:

```
module sub_module(input a , input b , output y);
	assign y = a & b;
endmodule

module multiple_module_opt2(input a , input b , input c , input d , output y);
		wire n1,n2,n3;
	sub_module U1 (.a(a) , .b(1'b0) , .y(n1));
	sub_module U2 (.a(b), .b(c) , .y(n2));
	sub_module U3 (.a(n2), .b(d) , .y(n3));
	sub_module U4 (.a(n3), .b(n1) , .y(y));
endmodule
```

On optimisation the above design becomes Y=0 

Run the below code for netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog multiple_module_opt2.v
synth -top multiple_module_opt2
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
flatten
show
write_verilog -noattr multiple_module_opt2_net.v
```

![image](https://github.com/user-attachments/assets/7e8c2f03-460e-4ebc-98f3-0a615f9843fc)

![image](https://github.com/user-attachments/assets/49b1c7fc-bb90-4964-aa7b-bd9b3567a8eb)


**Sequential Logic Optimizations**

**Example 1:**

Verilog code:

```
module dff_const1(input clk, input reset, output reg q);
always @(posedge clk, posedge reset)
begin
	if(reset)
		q <= 1'b0;
	else
		q <= 1'b1;
end
endmodule
```

Run the below code for netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const1.v
synth -top dff_const1
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const1_net.v
```

![image](https://github.com/user-attachments/assets/f2f3533f-b135-4948-ac9b-164b1505a02a)

![image](https://github.com/user-attachments/assets/0bb44777-718e-4c04-98b1-c77cf4d37bb3)


GTKWave Output:

```
iverilog dff_const1.v tb_dff_const1.v
./a.out
gtkwave tb_dff_const1.vcd
```

![image](https://github.com/user-attachments/assets/8f166a85-d3c8-441d-b825-8a02346adf69)



**Example 2:**

Verilog code:

```
module dff_const2(input clk, input reset, output reg q);
always @(posedge clk, posedge reset)
begin
	if(reset)
		q <= 1'b1;
	else
		q <= 1'b1;
end
endmodule
```

Run the below code for netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const2.v
synth -top dff_const2
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const2_net.v
```
![image](https://github.com/user-attachments/assets/bee0000e-99b3-4003-a617-b17a53c7bf03)

![image](https://github.com/user-attachments/assets/80ae8814-f92b-4b58-8e1d-a197eeb18593)


GTKWave Output:

```
iverilog dff_const2.v tb_dff_const2.v
./a.out
gtkwave tb_dff_const2.vcd
```

![image](https://github.com/user-attachments/assets/38835e07-c781-4279-ac70-c455d72fb3da)


**Example 3:**

Verilog code:

```
module dff_const3(input clk, input reset, output reg q);
reg q1;

always @(posedge clk, posedge reset)
begin
	if(reset)
	begin
		q <= 1'b1;
		q1 <= 1'b0;
	end
	else
	begin
		q1 <= 1'b1;
		q <= q1;
	end
end
endmodule
```

Run the below code for netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const3.v
synth -top dff_const3
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const3_net.v
```
![Screenshot from 2024-10-21 23-53-42](https://github.com/user-attachments/assets/cbbaa261-53f0-4c47-99de-5e4a1d682a51)

![image](https://github.com/user-attachments/assets/a8becf85-c765-4b36-9f79-43f4baa0e5e6)



GTKWave Output:

```
iverilog dff_const3.v tb_dff_const3.v
./a.out
gtkwave tb_dff_const3.vcd
```

![image](https://github.com/user-attachments/assets/704bdf19-301d-4e11-8131-5d615e34e911)


**Example 4:**

Verilog code:

```
module dff_const4(input clk, input reset, output reg q);
reg q1;

always @(posedge clk, posedge reset)
begin
	if(reset)
	begin
		q <= 1'b1;
		q1 <= 1'b1;
	end
else
	begin
		q1 <= 1'b1;
		q <= q1;
	end
end
endmodule
```

Run the below code for netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const4.v
synth -top dff_const4
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const4_net.v
```
![image](https://github.com/user-attachments/assets/e7ddc58e-182a-4b3f-8eb1-38647c5fcff3)


![image](https://github.com/user-attachments/assets/cc08fc4b-8577-44dd-9707-270e5715851c)


 
GTKWave Output:

```
iverilog dff_const4.v tb_dff_const4.v
./a.out
gtkwave tb_dff_const4.vcd
```

![image](https://github.com/user-attachments/assets/9b413497-2ee9-41f9-9dca-7ffac9b2d7f1)


**Example 5:**

Verilog code:

```
module dff_const5(input clk, input reset, output reg q);
reg q1;
always @(posedge clk, posedge reset)
	begin
		if(reset)
		begin
			q <= 1'b0;
			q1 <= 1'b0;
		end
	else
		begin
			q1 <= 1'b1;
			q <= q1;
		end
	end
endmodule
```

Run the below code for netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const5.v
synth -top dff_const5
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const5_net.v
```

![image](https://github.com/user-attachments/assets/8cd16a84-c1cf-42b0-8bed-30b580bb206f)

![image](https://github.com/user-attachments/assets/60d02237-77f6-4250-9b8b-2b3d23e6a1a0)



GTKWave Output:

```
iverilog dff_const5.v tb_dff_const5.v
./a.out
gtkwave tb_dff_const5.vcd
```

![image](https://github.com/user-attachments/assets/5b99179b-5d7f-4345-9afb-7e51cab20afb)



**Sequential Logic Optimizations for unused outputs**

**Example 1:**

Verilog code:

```
module counter_opt (input clk , input reset , output q);
reg [2:0] count;
assign q = count[0];
always @(posedge clk ,posedge reset)
begin
	if(reset)
		count <= 3'b000;
	else
		count <= count + 1;
end
endmodule
```

Run the below code for netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog counter_opt.v
synth -top counter_opt
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr counter_opt_net.v
```

![image](https://github.com/user-attachments/assets/275169b8-ab48-46f6-8eea-661e098025bc)

![image](https://github.com/user-attachments/assets/de54ef93-3e97-48b2-8752-56f218b8692b)



GTKWave Output:

```
iverilog counter_opt.v tb_counter_opt.v
./a.out
gtkwave tb_counter_opt.vcd
```
![image](https://github.com/user-attachments/assets/9463a18c-627d-450c-9de8-4e255eebd9f0)

Modified counter logic:

Verilog code:

```
module counter_opt (input clk , input reset , output q);
reg [2:0] count;
assign q = {count[2:0]==3'b100};
always @(posedge clk ,posedge reset)
begin
if(reset)
	count <= 3'b000;
else
	count <= count + 1;
end
endmodule
```
Run the below code for netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog counter_opt2.v
synth -top counter_opt
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr counter_opt2_net.v
```
![image](https://github.com/user-attachments/assets/5e870f18-59e5-4c3d-b19d-c19a95b723d2)

![image](https://github.com/user-attachments/assets/4677df33-bcdf-489e-b14b-7ba898c084d6)



GTKWave Output:

```
iverilog counter_opt.v tb_counter_opt.v
./a.out
gtkwave tb_counter_opt.vcd
```
![image](https://github.com/user-attachments/assets/1c76726f-7400-4202-9b52-93007870c9e2)

</details>
<details>
<summary>Day-4</summary>
<br>

##  GLS, Blocking vs Non-Blocking statements:

### Task 1: Gate Level Simulation (GLS):

Gate Level Simulation is a vital step in verifying digital circuits. It involves simulating the synthesized netlist—a lower-level representation of the design—using a testbench to verify logical correctness and timing behavior. By comparing the simulated outputs with the expected results, GLS ensures that synthesis has not introduced any errors and that the design meets performance requirements.

![image](https://github.com/user-attachments/assets/de76b0ed-1da9-48b5-b215-71350348f87d)


Accurate sensitivity lists are critical for ensuring correct circuit behavior. Incomplete sensitivity lists may result in unexpected latches. Similarly, blocking and non-blocking assignments within `always` blocks exhibit different execution behaviors. Incorrect use of blocking assignments may unintentionally create latches, leading to synthesis and simulation mismatches. To avoid these issues, circuit behavior should be carefully analyzed to ensure proper sensitivity lists and assignment usage.

***GLS Example 1: 2-to-1 MUX using Ternary Operator***

Verilog code:
```
module ternary_operator_mux (input i0, input i1, input sel, output y);
assign y = sel ? i1 : i0;
endmodule
```

Simulation steps:
```
iverilog ternary_operator_mux.v tb_ternary_operator_mux.v
./a.out
gtkwave tb_ternary_operator_mux.vcd
```

![Screenshot from 2024-10-21 23-11-39](https://github.com/user-attachments/assets/8ddc3718-9c16-4e4b-9152-4c7b347e738c)



***Synthesis:***
```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog ternary_operator_mux.v
synth -top ternary_operator_mux
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr ternary_operator_mux_net.v
!gedit ternary_operator_mux_net.v
```


![Screenshot from 2024-10-21 23-13-40](https://github.com/user-attachments/assets/6077f8ef-5d45-49e8-89fd-5c23c98cf8da)

![Screenshot from 2024-10-21 23-13-24](https://github.com/user-attachments/assets/cc777fc0-eb97-4328-8beb-d7b0c1647049)

![Screenshot from 2024-10-21 23-14-30](https://github.com/user-attachments/assets/1cf0e463-a5c7-4d82-b71e-657ba92c688e)

### Task 2: GLS Execution

```
cd ~/VLSI/sky130RTLDesignAndSynthesisWorkshop/verilog_files
iverilog ../my_lib/verilog_model/primitives.v ../my_lib/verilog_model/sky130_fd_sc_hd.v ternary_operator_mux_net.v tb_ternary_operator_mux.v
./a.out
gtkwave tb_ternary_operator_mux.vcd
```

![Screenshot from 2024-10-21 23-17-14](https://github.com/user-attachments/assets/92259c06-4b25-4901-a7da-35ea5f313ed4)


***Example 2: 2-to-1 Bad MUX Design***

Verilog code:
```
module bad_mux(input i0, input i1, input sel, output reg y);
    always@(sel) begin
        if(sel) y <= i1;
        else y <= i0;
    end
endmodule
```

Simulation steps:
```
iverilog bad_mux.v tb_bad_mux.v
./a.out
gtkwave tb_bad_mux.vcd
```

![image](https://github.com/user-attachments/assets/855dbd94-9f3b-47ea-9660-b95d997954f1)


### Synthesis:
```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib  
read_verilog bad_mux.v
synth -top bad_mux
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
show
write_verilog -noattr bad_mux_net.v
```


![Screenshot from 2024-10-21 23-24-23](https://github.com/user-attachments/assets/ea20763b-828b-4d66-b85f-e758d551eaa3)
![Screenshot from 2024-10-21 23-24-00](https://github.com/user-attachments/assets/0a692192-4cbf-4dcd-8eb9-3170c434f2f5)
![Screenshot from 2024-10-21 23-23-48](https://github.com/user-attachments/assets/51964979-9c23-47a8-9334-fad65b40fb1b)


### Gate Level Synthesis

Navigate to the appropriate directory and simulate:
```
iverilog ../my_lib/verilog_model/primitives.v ../my_lib/verilog_model/sky130_fd_sc_hd.v bad_mux.v tb_bad_mux.v
./a.out
gtkwave tb_bad_mux.vcd
```

![image](https://github.com/user-attachments/assets/0f844ecc-027a-4ee7-b72a-bdbce550d699)



The displayed waveforms represent the results of the Gate Level Synthesis (GLS) for the Bad MUX design shows correct result after GLS.

### Example 3: Blocking Caveat

Verilog code:
```
module blocking_caveat(input a, input b, input c, output reg d);
    reg x;
    always@(*) begin
        d = x & c;
        x = a | b;
    end
endmodule
```

Simulation steps:
```
iverilog blocking_caveat.v tb_blocking_caveat.v
./a.out
gtkwave tb_blocking_caveat.vcd
```

![image](https://github.com/user-attachments/assets/31c491b1-1efb-4356-87da-d3528462cdea)


As shown in the waveform, when both A and B are zero, the expected output of the OR gate (X) should be zero, which would result in the AND gate output (D) also being zero. However, due to the blocking assignment in the design, the AND gate input X retains the previous value of A|B, which is one. This leads to a mismatch between the expected and actual output, highlighting the discrepancy caused by the blocking statement.

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib  
read_verilog blocking_caveat.v
synth -top blocking_caveat
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
show
write_verilog -noattr blocking_caveat_net.v
!gedit blocking_caveat_net.v
```
![image](https://github.com/user-attachments/assets/f2c7fbc6-78f5-4e36-a235-0dceba648040)
![image](https://github.com/user-attachments/assets/d13ad889-8601-40f0-b62a-2f01358d97e9)
![image](https://github.com/user-attachments/assets/c8a8d841-096c-4c27-8aa0-6f2a567e5146)


### Gate Level Synthesis

Navigate to the appropriate directory and simulate:
```
iverilog ../my_lib/verilog_model/primitives.v ../my_lib/verilog_model/sky130_fd_sc_hd.v blocking_caveat_net.v tb_blocking_caveat.v
./a.out
gtkwave tb_blocking_caveat.vcd
```
![image](https://github.com/user-attachments/assets/878bda15-fbb0-4716-a658-0103b7ed9089)


These waveforms illustrate how the design behaves at the gate level simulations with respect to the blocking assignment issue.

</details>


