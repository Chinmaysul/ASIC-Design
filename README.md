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

# ASSIGNMENT 2: RISC-V Synthesis and compare output with functional simulation

Copy the src folder from your VSDBabySoC folder into your sky130RTLDesignAndSynthesisWorkshop folder

![Screenshot from 2024-10-23 23-43-16](https://github.com/user-attachments/assets/80d66f5d-46fd-49e5-bdda-a956d25547d9)
![image](https://github.com/user-attachments/assets/89945373-3ec7-4473-b804-4367b21e5487)



### Synthesis: 
```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog clk_gate.v
read_verilog rvmyth.v
synth -top rvmyth
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
write_verilog -noattr rvmyth.v
!gedit rvmyth.v

```
![Screenshot from 2024-10-23 23-49-58](https://github.com/user-attachments/assets/fc3639ae-b5dc-4868-95ab-29f4afaf42ec)
![Screenshot from 2024-10-23 23-51-37](https://github.com/user-attachments/assets/5d38a3c1-8241-4150-9763-93591df28aef)


```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_liberty -lib ../lib/avsddac.lib
read_liberty -lib ../lib/avsdpll.lib  
read_verilog vsdbabysoc.v
read_verilog rvmyth.v
read_verilog clk_gate.v 
synth -top vsdbabysoc
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
show
write_verilog -noattr vsdbabysoc.synth.v
```
![image](https://github.com/user-attachments/assets/98a1b032-cae0-4f97-b16d-91b52c070292)
![Screenshot from 2024-10-24 01-03-53](https://github.com/user-attachments/assets/956054fb-5555-4e76-82bd-653e7480a53b)
![Screenshot from 2024-10-24 01-01-01](https://github.com/user-attachments/assets/6ca72a88-b1a5-45d4-89e7-f70e6f83929f)

### Generate GTKWave simulations:
```
iverilog ../../my_lib/verilog_model/primitives.v ../../my_lib/verilog_model/sky130_fd_sc_hd.v rvmyth.v testbench.v vsdbabysoc.v avsddac.v avsdpll.v clk_gate.v
./a.out
gtkwave dump.vcd
```
![image](https://github.com/user-attachments/assets/264af632-f336-4eb4-ba30-d1982efb8c3d)
![Screenshot from 2024-10-24 01-56-24](https://github.com/user-attachments/assets/6c677293-54af-4ac8-bf2d-a166ea909598)
![image](https://github.com/user-attachments/assets/7db4fc12-0089-45a8-94ae-a290ed7e633e)



 ### Functional Simulations
 ```
cd ~
cd VSDBabySoC
iverilog -o ./pre_synth_sim.out -DPRE_SYNTH_SIM src/module/testbench.v -I src/include -I src/module/
./pre_synth_sim.out
gtkwave pre_synth_sim.vcd
```

![image](https://github.com/user-attachments/assets/f4a6cf64-a034-4385-9631-5877a44ffa80)

![Screenshot from 2024-10-24 00-02-07](https://github.com/user-attachments/assets/eac15cda-838d-441c-a074-51a9b6ac28b1)

As we can see comparing both the outputs are same hence verifying our results.

![Screenshot from 2024-10-24 01-57-11](https://github.com/user-attachments/assets/a83d658d-4fa0-4c0b-b48a-e621f039024e)


# ASSIGNMENT 3: Post Synthesis Static Timing Analysis using OpenSTA

First, write the contents of the .sdc in vsdbabysoc_synthesis.sdc:

```
cd VSDBabySoc/src/sdc
gedit vsdbabysoc_synthesis.sdc

```

```
set PERIOD 11.75

set_units -time ns
create_clock [get_pins {pll/CLK}] -name clk -period $PERIOD
set_clock_uncertainty -setup  [expr $PERIOD * 0.05] [get_clocks clk]
set_clock_transition [expr $PERIOD * 0.05] [get_clocks clk]
set_clock_uncertainty -hold [expr $PERIOD * 0.08] [get_clocks clk]
set_input_transition [expr $PERIOD * 0.08] [get_ports ENb_CP]
set_input_transition [expr $PERIOD * 0.08] [get_ports ENb_VCO]
set_input_transition [expr $PERIOD * 0.08] [get_ports REF]
set_input_transition [expr $PERIOD * 0.08] [get_ports VCO_IN]
set_input_transition [expr $PERIOD * 0.08] [get_ports VREFH]
```

To run OpenSTA, run the following commands:

```
cd VSDBabySoc/src
sta
read_liberty -min ./lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_liberty -min ./lib/avsdpll.lib
read_liberty -min ./lib/avsddac.lib
read_liberty -max ./lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_liberty -max ./lib/avsdpll.lib
read_liberty -max ./lib/avsddac.lib
read_verilog ../output/synth/vsdbabysoc.synth.v
link_design vsdbabysoc
read_sdc ./sdc/vsdbabysoc_synthesis.sdc
report_checks -path_delay min_max -format full_clock_expanded -digits 4
```
![image](https://github.com/user-attachments/assets/849f95fc-6584-495c-b46e-c9a1337bb4b1)
![image](https://github.com/user-attachments/assets/05ff3192-d063-4540-a9d5-76ac25f1119e)
![image](https://github.com/user-attachments/assets/49122d0a-2b33-4a20-a206-736c43337118)


# ASSIGNMENT 4: Post Synthesis Static Timing Analysis using OpenSTA 

Snapshot of the sdc file vsdbabysoc_synthesis.sdc:
```
set PERIOD 11.75
set_units -time ns
create_clock [get_pins {pll/CLK}] -name clk -period $PERIOD
set_clock_uncertainty -setup  [expr $PERIOD * 0.05] [get_clocks clk]
set_clock_transition [expr $PERIOD * 0.05] [get_clocks clk]
set_clock_uncertainty -hold [expr $PERIOD * 0.08] [get_clocks clk]
set_input_transition [expr $PERIOD * 0.08] [get_ports ENb_CP]
set_input_transition [expr $PERIOD * 0.08] [get_ports ENb_VCO]
set_input_transition [expr $PERIOD * 0.08] [get_ports REF]
set_input_transition [expr $PERIOD * 0.08] [get_ports VCO_IN]
set_input_transition [expr $PERIOD * 0.08] [get_ports VREFH]
```

![Screenshot 2024-11-01 150250](https://github.com/user-attachments/assets/9ccc3417-e80d-4852-99d7-a437f8906570)


Store all the `lib` files in the `lib` folder in the `VSDBabySoC/src` directory.

![image](https://github.com/user-attachments/assets/927750f8-fd2a-4ce3-bf97-c2c734652ded)


Now create a `sta_pvt.tcl` file with the following content.

```
gedit sta_pvt.tcl
```
```
set list_of_lib_files(1) "sky130_fd_sc_hd__ff_100C_1v65.lib"
set list_of_lib_files(2) "sky130_fd_sc_hd__ff_100C_1v95.lib"
set list_of_lib_files(3) "sky130_fd_sc_hd__ff_n40C_1v56.lib"
set list_of_lib_files(4) "sky130_fd_sc_hd__ff_n40C_1v65.lib"
set list_of_lib_files(5) "sky130_fd_sc_hd__ff_n40C_1v76.lib"
set list_of_lib_files(6) "sky130_fd_sc_hd__ff_n40C_1v95.lib"
set list_of_lib_files(7) "sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part1"
set list_of_lib_files(8) "sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part2"
set list_of_lib_files(9) "sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part3"
set list_of_lib_files(10) "sky130_fd_sc_hd__ss_100C_1v40.lib"
set list_of_lib_files(11) "sky130_fd_sc_hd__ss_100C_1v60.lib"
set list_of_lib_files(12) "sky130_fd_sc_hd__ss_n40C_1v28.lib"
set list_of_lib_files(13) "sky130_fd_sc_hd__ss_n40C_1v35.lib"
set list_of_lib_files(14) "sky130_fd_sc_hd__ss_n40C_1v40.lib"
set list_of_lib_files(15) "sky130_fd_sc_hd__ss_n40C_1v44.lib"
set list_of_lib_files(16) "sky130_fd_sc_hd__ss_n40C_1v60.lib"
set list_of_lib_files(17) "sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part1"
set list_of_lib_files(18) "sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part2"
set list_of_lib_files(19) "sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part3"
set list_of_lib_files(20) "sky130_fd_sc_hd__ss_n40C_1v76.lib"
set list_of_lib_files(21) "sky130_fd_sc_hd__tt_025C_1v80.lib"
set list_of_lib_files(22) "sky130_fd_sc_hd__tt_100C_1v80.lib"

for {set i 1} {$i <= [array size list_of_lib_files]} {incr i} {
read_liberty ./lib/$list_of_lib_files($i)
read_verilog ../output/synth/vsdbabysoc.synth.v
link_design vsdbabysoc
read_sdc ./sdc/vsdbabysoc_synthesis.sdc
check_setup -verbose
report_checks -path_delay min_max -fields {nets cap slew input_pins fanout} -digits {4} > ./sta_output/min_max_$list_of_lib_files($i).txt

}
```

![image](https://github.com/user-attachments/assets/8511fc7f-c03a-45af-9349-d3984e180232)

Create a folder named `sta_output` in `VSDBabySoC/src` to store the output txt files.
Now, run the following commands:

```
cd VSDBabySoC/src
sta
source sta_pvt.tcl
```

![image](https://github.com/user-attachments/assets/b74d36fb-3d69-4168-84e2-d0b839268159)
![image](https://github.com/user-attachments/assets/cfe93b3d-a0b6-47bc-8b5e-05f94bdb334a)
![image](https://github.com/user-attachments/assets/c7bc6102-63bf-4c9c-bc19-968e339bf778)



These `.txt` file will be generated as shown

![image](https://github.com/user-attachments/assets/37cc8ee0-f23b-4832-ba62-2a88e4515d0a)
![image](https://github.com/user-attachments/assets/8a7d0c11-5706-48b0-88af-5ca8d27b5f64)



Now put the values in excel and plot the graphs as shown:

![image](https://github.com/user-attachments/assets/1361412f-06b3-4c28-9c44-cec792612b5e)
![image](https://github.com/user-attachments/assets/8754ea4e-b157-46f1-8ca6-2e05512e8d57)
![image](https://github.com/user-attachments/assets/09962b6c-929d-4f92-a8aa-dc34dc989149)

# ASSIGNMENT 5: Advanced Physical Design using OpenLane using Sky130
<details>
<summary> Day-1 </summary>
<br>
	
### Task 1: Open-source EDA, OpenLane and Sky130 PDK

**QFN-48 Package:** A Quad Flat No-leads (QFN) 48 package is a leadless IC package with 48 connection pads around the perimeter. It offers good thermal and electrical performance in a compact form, making it ideal for high-density applications.

![image](https://github.com/user-attachments/assets/2237a9ef-dc38-444f-97a5-ceb4e983c8f0)


**Chip:** An integrated circuit (IC) that contains various functional blocks like memory, processing units, and I/O in a silicon substrate, typically used for specific applications in electronics.

![image](https://github.com/user-attachments/assets/7503bcea-4654-4bc9-b77a-de9ced7929be)


**Pads:** Small metallic areas on a chip or package used to connect internal circuitry to external connections, enabling signals to be transferred to and from the IC.

**Core:** The central part of a chip containing the main processing unit and functional logic, often optimized for power and performance.

**Die:** The section of a silicon wafer containing an individual IC before it is packaged, housing all active circuits and elements for the chip's functions.

![image](https://github.com/user-attachments/assets/cfa2c482-59c5-4ad5-b74c-a027bfdf16b8)


**IPs (Intellectual Properties):** Pre-designed functional blocks or modules within a chip, such as USB controllers or memory interfaces, licensed for reuse across various designs to save time and cost.

![image](https://github.com/user-attachments/assets/1039a7d9-0286-42c7-8da7-17136c3da5aa)


**From Software Applications to Hardware Flow**

To run an application on hardware, several processes take place. First, the application enters a layer known as the system software, which prepares it for execution by translating the application program into binary format, understandable by hardware. Key components within system software include the Operating System (OS), Compiler, and Assembler.

The process starts with the OS, which breaks down application functions written in high-level languages such as C, C++, Java, or Visual Basic. These functions are passed to a suitable compiler, which translates them into low-level instructions. The syntax and format of these instructions are tailored to the specific hardware architecture in use.

Next, the assembler converts these hardware-specific instructions into binary format, known as machine language. This binary code is then fed to the hardware, enabling it to perform specific tasks as defined by the received instructions.

![image](https://github.com/user-attachments/assets/14788472-7c91-4860-82c6-2bccb49f91d2)


![image](https://github.com/user-attachments/assets/cabbd8f7-f0c4-4a13-bf2e-d6d67392910e)

For the above stopwatch the below figure shows the input and output of the compiler and assembler.

![image](https://github.com/user-attachments/assets/63f2e771-eed8-4953-b501-dd9ff0d209f7)

The compiler generates architecture-specific instructions, while the assembler produces the corresponding binary patterns. To execute these instructions on hardware, an RTL (written in a Hardware Description Language) is used to interpret and implement the instructions. This RTL design is then synthesized into a netlist, represented as interconnected logic gates. Finally, the netlist undergoes physical design implementation to be fabricated onto the chip.


**Components of ASIC Design**

![image](https://github.com/user-attachments/assets/560b728b-8e75-4c9d-a3c8-5b640318c4aa)

- RTL IPs: Pre-designed, verified digital circuit blocks (like adders, flip-flops, memory) in HDL (e.g., Verilog, VHDL). They save design time by providing ready-to-use components for complex circuits.

- EDA Tools: Software that automates ASIC design tasks (e.g., synthesis, optimization, placement, timing analysis). Essential for improving productivity and ensuring performance and power requirements are met.

- PDK Data: A set of files and parameters from a semiconductor foundry, detailing its manufacturing process (e.g., transistor models, design rules). PDKs ensure ASIC designs are compatible with the foundry’s fabrication process.

**RTL to GDS flow**

- **RTL Design:** Describes the circuit's functional behavior using HDLs like Verilog or VHDL, defining its logic and data paths.

- **RTL Synthesis:** Converts RTL code to a gate-level netlist which is a collection of standard cells like AND gates, flip-flops, and multiplexers by mapping it to standard cells and optimizing for area, power, and timing. 

- **Floor and Power Planning:** Partitions chip area, places major components, and defines power grid and I/O placement to optimize area, power distribution, and signal flow. This step optimizes the physical layout, aiming to reduce power consumption and improve signal integrity by considering the placement of I/O pads and power distribution cells

- **Placement:** Assigns physical locations to cells, aiming to minimize wirelength, reduce signal delay, and meet design constraints. The placement tool carefully arranges the cells to balance the overall chip design for optimal performance and area utilization.

- **Clock Tree Synthesis (CTS):** Clock Tree Synthesis (CTS) is a critical step that focuses on creating an optimized clock distribution network. CTS ensures the clock is distributed evenly to all flip-flops and registers. It builds an optimized clock network to balance clock signal distribution and reduce clock skew.

- **Routing:** Connects components based on placement, optimizing wire paths to ensure signal integrity, minimize congestion, and meet design rules.

- **Sign-off:** Final verification stage, ensuring the design meets functionality, performance, power, and reliability targets. Timing analysis is performed to check setup and hold times, power analysis ensures the design doesn’t exceed power limits, and physical verification checks ensure that the layout meets manufacturing rules. This stage confirms the design is ready for fabrication.

- **GDSII File Generation:** Creates the GDSII file containing the complete layout details needed for chip fabrication. This file represents the final physical design and is used by manufacturers to create the photomasks required for chip production. The GDSII file serves as the blueprint for the actual fabrication of the chip.

**OpenLane ASIC Flow:**

![image](https://github.com/user-attachments/assets/cdd04b14-fbfe-44a3-8d4e-8fbfe443bd74)

1. RTL Synthesis, Technology Mapping, and Formal Verification: The tools used are Yosys (for RTL synthesis), ABC (for technology mapping and formal verification).
2. Static Timing Analysis: The tools used are OpenSTA (for static timing analysis).
3. Floor Planning: The tools used are init_fp (initial floorplanning), ioPlacer (I/O placement), pdn (power distribution network planning), tapcell (tap cell insertion).
4. Placement: The tools used are RePLace (global placement), Resizer (optional for resizing cells), OpenPhySyn (formerly used for placement), OpenDP (detailed placement).
5. Clock Tree Synthesis: The tools used are TritonCTS (for clock tree synthesis).
6. Fill Insertion: The tools used are OpenDP (for filler placement).
7. Routing: The tools used for global routing are FastRoute or CU-GR (formerly used) and for the detailed routing , we use TritonRoute (for detailed routing) or DR-CU (formerly used).
8. SPEF Extraction: The tools used are OpenRCX (or SPEF-Extractor, formerly used) for Standard Parasitic Exchange Format (SPEF) extraction.
9. GDSII Streaming Out: The tools used are Magic and KLayout (for viewing and editing GDSII files).
10. Design Rule Checking (DRC) Checks: The tools used are Magic and KLayout (for DRC checks).
11. Layout vs. Schematic (LVS) Check: The tools used are Netgen (for LVS checks).
12. Antenna Checks: The tools used are Magic (for antenna checks).

**OpenLANE Directory structure**

``` 
├── OOpenLane             -> directory where the tool can be invoked (run docker first)
│   ├── designs          -> All designs must be extracted from this folder
│   │   │   ├── picorv32a -> Design used as case study for this workshop
│   |   |   ├── ...
|   |   ├── ...
├── pdks                 -> contains pdk related files 
│   ├── skywater-pdk     -> all Skywater 130nm PDKs
│   ├── open-pdks        -> contains scripts that makes the commerical PDK (which is normally just compatible to commercial tools) to also be compatible with the open-source EDA tool
│   ├── sky130A          -> pdk variant made especially compatible for open-source tools
│   │   │  ├── libs.ref  -> files specific to node process (timing lib, cell lef, tech lef) for example is `sky130_fd_sc_hd` (Sky130nm Foundry Standard Cell High Density)  
│   │   │  ├── libs.tech -> files specific for the tool (klayout,netgen,magic...) 
```

**Synthesis in Openlane:**

Run the following:

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
run_synthesis

```
![image](https://github.com/user-attachments/assets/6a91d34d-d49f-4c95-ab3e-3ede945c4d03)


![image](https://github.com/user-attachments/assets/86d6f601-4228-499d-bff7-3bdb91cba919)


To view the netlist:

```
cd designs/picorv32a/runs/09-11_06-33/results/synthesis/
gedit picorv32a.synthesis.v
```

![image](https://github.com/user-attachments/assets/0a6405fa-e4c0-41f6-a8ba-2c2f8c018395)
![image](https://github.com/user-attachments/assets/fec4da7d-6f7b-48f7-9d55-9e742d7db7eb)



To view the yosys report:

```
cd ../..
cd reports/synthesis
gedit 1-yosys_4.stat.rpt
```
![image](https://github.com/user-attachments/assets/923d26e1-8ca7-487f-9eca-4b92d4bed4bb)

![image](https://github.com/user-attachments/assets/25731da9-2a73-4ce6-a752-541af4e51e92)



Report:

```
28. Printing statistics.

=== picorv32a ===

   Number of wires:              14596
   Number of wire bits:          14978
   Number of public wires:        1565
   Number of public wire bits:    1947
   Number of memories:               0
   Number of memory bits:            0
   Number of processes:              0
   Number of cells:              14876
     sky130_fd_sc_hd__a2111o_2       1
     sky130_fd_sc_hd__a211o_2       35
     sky130_fd_sc_hd__a211oi_2      60
     sky130_fd_sc_hd__a21bo_2      149
     sky130_fd_sc_hd__a21boi_2       8
     sky130_fd_sc_hd__a21o_2        57
     sky130_fd_sc_hd__a21oi_2      244
     sky130_fd_sc_hd__a221o_2       86
     sky130_fd_sc_hd__a22o_2      1013
     sky130_fd_sc_hd__a2bb2o_2    1748
     sky130_fd_sc_hd__a2bb2oi_2     81
     sky130_fd_sc_hd__a311o_2        2
     sky130_fd_sc_hd__a31o_2        49
     sky130_fd_sc_hd__a31oi_2        7
     sky130_fd_sc_hd__a32o_2        46
     sky130_fd_sc_hd__a41o_2         1
     sky130_fd_sc_hd__and2_2       157
     sky130_fd_sc_hd__and3_2        58
     sky130_fd_sc_hd__and4_2       345
     sky130_fd_sc_hd__and4b_2        1
     sky130_fd_sc_hd__buf_1       1656
     sky130_fd_sc_hd__buf_2          8
     sky130_fd_sc_hd__conb_1        42
     sky130_fd_sc_hd__dfxtp_2     1613
     sky130_fd_sc_hd__inv_2       1615
     sky130_fd_sc_hd__mux2_1      1224
     sky130_fd_sc_hd__mux2_2         2
     sky130_fd_sc_hd__mux4_1       221
     sky130_fd_sc_hd__nand2_2       78
     sky130_fd_sc_hd__nor2_2       524
     sky130_fd_sc_hd__nor2b_2        1
     sky130_fd_sc_hd__nor3_2        42
     sky130_fd_sc_hd__nor4_2         1
     sky130_fd_sc_hd__o2111a_2       2
     sky130_fd_sc_hd__o211a_2       69
     sky130_fd_sc_hd__o211ai_2       6
     sky130_fd_sc_hd__o21a_2        54
     sky130_fd_sc_hd__o21ai_2      141
     sky130_fd_sc_hd__o21ba_2      209
     sky130_fd_sc_hd__o21bai_2       1
     sky130_fd_sc_hd__o221a_2      204
     sky130_fd_sc_hd__o221ai_2       7
     sky130_fd_sc_hd__o22a_2      1312
     sky130_fd_sc_hd__o22ai_2       59
     sky130_fd_sc_hd__o2bb2a_2     119
     sky130_fd_sc_hd__o2bb2ai_2     92
     sky130_fd_sc_hd__o311a_2        8
     sky130_fd_sc_hd__o31a_2        19
     sky130_fd_sc_hd__o31ai_2        1
     sky130_fd_sc_hd__o32a_2       109
     sky130_fd_sc_hd__o41a_2         2
     sky130_fd_sc_hd__or2_2       1088
     sky130_fd_sc_hd__or2b_2        25
     sky130_fd_sc_hd__or3_2         68
     sky130_fd_sc_hd__or3b_2         5
     sky130_fd_sc_hd__or4_2         93
     sky130_fd_sc_hd__or4b_2         6
     sky130_fd_sc_hd__or4bb_2        2

   Chip area for module '\picorv32a': 147712.918400
```

```
Flop ratio = Number of D Flip flops = 1613  = 0.1084
             ______________________   _____
             Total Number of cells    14876
```
</details>

<details>
<summary>Day-2</summary>
<br>
	
### Good floorplan vs bad floorplan and introduction to library cells

Utilization Factor and Aspect Ratio: In IC floor planning, two critical parameters are the utilization factor and the aspect ratio. The utilization factor measures the area occupied by the netlist relative to the total core area. Although a utilization of 1 (or 100%) would be ideal, practical designs typically aim for a utilization factor between 0.5 and 0.6. This range provides space for buffer zones, routing channels, and potential future modifications. The aspect ratio, defined as the ratio of height to width, indicates the shape of the chip. An aspect ratio of 1 produces a square shape, while other values yield a rectangular layout. This ratio is determined based on functional requirements, packaging constraints, and manufacturing considerations.
```

Utilisation Factor =  Area occupied by netlist
                     __________________________
                         Total area of core
```                         
```
Aspect Ratio =  Height
               ________
                Width
```

**Pre-placed cells** : Pre-placed cells are essential functional blocks, such as memory, custom processors, and analog circuits, positioned manually in fixed locations. These blocks are crucial for the chip’s performance and remain fixed during placement and routing to preserve their functionality and layout integrity.

**Decoupling Capacitors** : Decoupling capacitors are placed near logic circuits to stabilize power supply voltages during transient events. Acting as local energy reserves, they help reduce voltage fluctuations, crosstalk, and electromagnetic interference (EMI), ensuring reliable power delivery to sensitive circuits.

**Power Planning**: A robust power planning strategy includes creating a power and ground mesh to distribute VDD and VSS evenly across the chip. This setup ensures stable power delivery, minimizes voltage drops, and improves overall efficiency. Multiple power and ground points reduce the risk of instability and voltage drop issues, supporting the design’s power needs effectively.

**Pin Placement**: Pin placement (I/O planning) is crucial for functionality and reliability. Strategic pin assignment minimizes signal degradation, preserves data integrity, and helps manage heat dissipation. Proper positioning of power and ground pins supports thermal management and enhances signal strength, contributing to overall system stability and manufacturability.

Floorplaning using OpenLANE:

Run the following commands:

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
```

```
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
run_synthesis
run_floorplan
```
![image](https://github.com/user-attachments/assets/947ba6a0-43ef-47be-b705-324914b7f814)
![image](https://github.com/user-attachments/assets/f9ed0d4e-6098-4f6b-8466-11556751c7c6)
![image](https://github.com/user-attachments/assets/225a82a5-39f0-4db0-8f18-a3e532f14949)


Now, run the below commands in a new terminal:

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/09-11_07-10/results/floorplan
gedit picorv32a.floorplan.def
```
![image](https://github.com/user-attachments/assets/a6908056-4b79-4dfa-bf43-5e1e02f26ec3)


According to floorplan definition:
```

1000 Unit Distance = 1 Micron  

Die width in unit distance = 660685

Die height in unit distance = 671405 

​Die width in microns = 660685/1000 = 660.685 Microns  

Die height in microns = 671405/1000 = 671.405 Microns  

Area of die in microns = 660.685 × 671.405 = 443587.212425 Square Microns
```


To view the floorplan in magic. Open a new terminal and run the below commands:

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/17-03_12-06/results/floorplan/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.floorplan.def &
```

![image](https://github.com/user-attachments/assets/a7390c8f-53fa-45f6-bf6e-07fbaf0d726d)
![image](https://github.com/user-attachments/assets/cc97b0b9-9322-4f22-bf62-1d4f1d380a3c)


Decap and Tap Cells:
![image](https://github.com/user-attachments/assets/bc9dbc11-01d1-4f04-b6f2-18b322e86924)

Equidistant placement of ports: 
![image](https://github.com/user-attachments/assets/259edddd-f013-4484-87e0-2cf290721ef2)


Unplaces standard cells at origin:
![image](https://github.com/user-attachments/assets/c5c3f28a-49b0-4e1e-a8b4-5139853ee268)

Command to run placement:

```
run_placement
```

To view the placement in magic:

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/17-03_12-06/results/placement/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.placement.def &
```

![image](https://github.com/user-attachments/assets/76db7b93-3d9f-4f8d-90a9-e8a24e29c8b7)

![image](https://github.com/user-attachments/assets/6f868524-175a-4244-aaa4-5a69de9fa102)


**Cell design and Characterization Flow**

Library is a place where we get information about every cell. It has differents cells with different size, functionality,threshold voltages. There is a typical cell design flow steps.

Inputs : PDKS(process design kit) : DRC & LVS, SPICE Models, library & user-defined specs.
Design Steps :Circuit design, Layout design (Art of layout Euler's path and stick diagram), Extraction of parasitics, Characterization (timing, noise, power).
Outputs: CDL (circuit description language), LEF, GDSII, extracted SPICE netlist (.cir), timing, noise and power .lib files

**Standard Cell Characterization Flow**

A typical standard cell characterization flow that is followed in the industry includes the following steps:

- Read in the models and tech files
- Read extracted spice Netlist
- Recognise behavior of the cells
- Read the subcircuits
- Attach power sources
- Apply stimulus to characterization setup
- Provide neccesary output capacitance loads
- Provide neccesary simulation commands
- Now all these 8 steps are fed in together as a configuration file to a characterization software called GUNA. This software generates timing, noise, power models. These .libs are classified as Timing characterization, power characterization and noise characterization.

**Timing parameters**

| Timing definition | Value |
|---|---|
| slew_low_rise_thr | 20% value |
| slew_high_rise_thr | 80% value |
| slew_low_fall_thr | 20% value |
| slew_high_fall_thr | 80% value |
| in_rise_thr | 50% value |
| in_fall_thr | 50% value |
| out_rise_thr | 50% value |
| out_fall_thr | 50% value |

**Propagation Delay**: It refers to the time it takes for a change in an input signal to reach 50% of its final value to produce a corresponding change in the output signal to reach 50% of its final value of a digital circuit.

```
rise delay =  time(out_fall_thr) - time(in_rise_thr)
```

**Transistion time**: The time it takes the signal to move between states is the transition time , where the time is measured between 10% and 90% or 20% to 80% of the signal levels.

```
Fall transition time: time(slew_high_fall_thr) - time(slew_low_fall_thr)
Rise transition time: time(slew_high_rise_thr) - time(slew_low_rise_thr)
```
</details>
<details>
<summary>Day-3</summary>
<br>

### Design library cell using Magic Layout and ngspice characterization

**CMOS inverter ngspice simulations**

Creating a SPICE Deck for a CMOS Inverter Simulation

- Netlist Creation: Define the component connections (netlist) for a CMOS inverter circuit. Ensure each node is labeled appropriately for easy identification in the SPICE simulation. Typical nodes include input, output, ground, and supply nodes.
- Device Sizing: Specify the Width-to-Length (W/L) ratios for both the PMOS and NMOS transistors.For proper operation, the PMOS width should be larger than the NMOS width, usually 2x to 3x, to balance the drive strength
- Voltage Levels: Set gate and supply voltages, often in multiples of the transistor length. 
- Node Naming: Assign node names to each connection point around the components to clearly identify each element in the SPICE netlist (e.g., VDD, GND, IN, OUT). This helps SPICE recognize each component and simulate the circuit effectively.
  

```
***syntax for PMOS and NMOS desription***
[component name] [drain] [gate] [source] [substrate] [transistor type] W=[width] L=[length]

 ***simulation commands***
.op --- is the start of SPICE simulation operation where Vin sweeps from 0 to 2.5 with 0.5 steps
tsmc_025um_model.mod  ----  model file which contains the technological parameters for the 0.25um NMOS and PMOS 
```
Commands to simulate in SPICE:

```
source [filename].cir
run
setplot 
dc1 
plot out vs in 
```

![image](https://github.com/user-attachments/assets/49f1ed28-c601-4954-a3aa-077a2c650650)

The switching threshold Vm is like a critical voltage level for a component called a CMOS inverter. It's the point at which this inverter switches between sending out a "0" or a "1" in a computer chip. This the point where both PMOS and NMOS is in saturation or kind of turned on, and leakage current is high. If PMOS is thicker than NMOS, the CMOS will have higher switching threshold (1.2V vs 1V) while threshold will be lower when NMOS becomes thicker.

At this point, both the transistors are in saturation region, means both are turned on and have high chances of current flowing directly from VDD to Ground called Leakage current.




Now, we clone the custom inverter

```
cd Desktop/work/tools/openlane_working_dir/openlane
git clone https://github.com/nickson-jose/vsdstdcelldesign
cd vsdstdcelldesign
cp /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech .
ls
magic -T sky130A.tech sky130_inv.mag &
```

![image](https://github.com/user-attachments/assets/3b21d02b-71d6-4b46-8987-14d90ecb7383)

![image](https://github.com/user-attachments/assets/583afeb2-7587-4564-9ee1-68290324ee1a)



**Inception of Layout CMOS fabrication process**

The 16-mask CMOS design fabrication process:

1. Substrate Preparation: The process begins with preparing a silicon wafer as the foundational substrate for the circuit.
2. N-Well Formation: The N-well regions are created on the substrate by introducing impurities, typically phosphorus, through ion implantation or diffusion
3. P-Well Formation: Similar to the N-well formation, P-well regions are created using ion implantation or diffusion with boron or other suitable dopants.
4. Gate Oxide Deposition: A thin silicon dioxide layer is deposited to form the gate oxide, which insulates the gate from the channel.
5. Poly-Silicon Deposition: A layer of polysilicon is deposited on the gate oxide to serve as the gate electrode.
6. Poly-Silicon Masking and Etching: A photoresist mask defines areas where polysilicon should remain, and etching removes exposed portions.
7. N-Well Masking and Implantation: A photoresist mask is used to define the areas where the N-well regions should be preserved. Phosphorus or other suitable impurities are then implanted into the exposed regions.
8. P-Well Masking and Implantation: Similarly, a photoresist mask is used to define the areas where the P-well regions should be preserved. Boron or other suitable impurities are implanted into the exposed regions.
9. Source/Drain Implantation: Using photoresist masks, dopants are implanted to create source and drain regions (e.g., arsenic for NMOS, boron for PMOS).
10. Gate Formation: The gate electrode is defined by etching the poly-silicon layer using a photoresist mask.
11. Source/Drain Masking and Etching: A photoresist mask is applied to define the source and drain regions followed by etching to remove the oxide layer in those areas.
12. Contact/Via Formation: Contact holes or vias are etched through the oxide layer to expose the underlying regions, such as the source/drain regions or poly-silicon gates.
13. Metal Deposition: A layer of metal, typically aluminum or copper, is deposited on the wafer surface to form the interconnects.
14. Metal Masking and Etching: A photoresist mask is used to define the metal interconnects, and etching is performed to remove the exposed metal, leaving behind the desired interconnect patterns.
15. Passivation Layer Deposition: A protective layer, often made of silicon dioxide or nitride, is deposited to isolate and shield the metal interconnects.
16. Final Testing and Packaging: The fabricated wafer undergoes rigorous testing to ensure the functionality of the integrated circuits. The working chips are then separated, packaged, and prepared for use in various electronic devices.


Inverter layout:

Identify NMOS:

![image](https://github.com/user-attachments/assets/7053fb7c-3108-45b6-8aa5-5c297716a990)


Identify PMOS:

![image](https://github.com/user-attachments/assets/6777f354-d1f8-4c9e-aa3b-aa390c3fc7ab)


Output Y:

![image](https://github.com/user-attachments/assets/f6a8a3de-e767-428a-8e00-10113f4378f7)


PMOS source connected to VDD:

![image](https://github.com/user-attachments/assets/eb64926c-080d-4b88-8f64-01c07361a30f)


NMOS source connected to VSS:

![image](https://github.com/user-attachments/assets/5e7dcc43-9225-48df-aa3c-95b4ef86cc58)


Spice extraction of inverter in Magic. Run these in the tkcon window:

```
# Check current directory
pwd
extract all
ext2spice cthresh 0 rthresh 0
ext2spice
```
![image](https://github.com/user-attachments/assets/b01c135f-e837-4e0a-937a-07b477192598)


To view the spice file:

![image](https://github.com/user-attachments/assets/0ab0f434-0785-41b4-aaad-70aa0738af86)

![Screenshot from 2024-11-15 02-55-15](https://github.com/user-attachments/assets/110969bb-3f4f-43ae-89a9-c3c3d8d353b5)

The contents of spice file:

```
* SPICE3 file created from sky130_inv.ext - technology: sky130A

.option scale=10n

.subckt sky130_inv A Y VPWR VGND
X0 Y A VGND VGND sky130_fd_pr__nfet_01v8 ad=1.37n pd=0.148m as=1.37n ps=0.148m w=35 l=23
X1 Y A VPWR VPWR sky130_fd_pr__pfet_01v8 ad=1.44n pd=0.152m as=1.52n ps=0.156m w=37 l=23
C0  A Y 0.754f
C1 A VPWR 0.0774f
C2 VPWR Y 0.11f
C3 Y VGND 0.279f
C4 A VGND 0.45f
C5 VPWR VGND 0.781f
.ends

```

Now modify the `sky130_inv.spice` file to find the transient respone:

```
* SPICE3 file created from sky130_inv.ext - technology: sky130A

.option scale=0.01u
.include ./libs/pshort.lib
.include ./libs/nshort.lib

//.subckt sky130_inv A Y VPWR VGND
M1000 Y A VGND VGND nshort_model.0 w=35 l=23
+  ad=1.44n pd=0.152m as=1.37n ps=0.148m
M1001 Y A VPWR VPWR pshort_model.0 w=37 l=23
+  ad=1.44n pd=0.152m as=1.52n ps=0.156m

VDD VPWR 0 3.3V
VSS VGND 0 0V
Va A VGND PULSE(0V 3.3V 0 0.1ns 0.1ns 2ns 4ns)

C0 A VPWR 0.0774f
C1 VPWR Y 0.117f
C2 A Y 0.0754f
C3 Y VGND 2f
C4 A VGND 0.45f
C5 VPWR VGND 0.781f
//.ends

.tran 1n 20n
.control
run
.endc
.end
```

Now, simulate the spice netlist
```
ngspice sky130_inv.spice
```
![image](https://github.com/user-attachments/assets/aac08914-d9fd-4483-bf4e-78d341bd1f53)


To plot the waveform:

```
plot y vs time a
```
![image](https://github.com/user-attachments/assets/42338b1c-1274-43db-b450-747554f42982)

![image](https://github.com/user-attachments/assets/9cbaf59d-f58c-467f-b3b3-b945cbb615ee)

Using this transient response, we will now characterize the cell's slew rate and propagation delay:

Rise Transition: Time taken for the output to rise from 20% to 80% of max value
Fall Transition: Time taken for the output to fall from 80% to 20% of max value
Cell Rise delay: difference in time(50% output rise) to time(50% input fall)
Cell Fall delay: difference in time(50% output fall) to time(50% input rise)

```
20% of output(3.3V) = 0.66V
80% of output(3.3V) = 2.64V
50% of output(3.3V) = 1.15V
```
20% Screenshots:

![image](https://github.com/user-attachments/assets/7f1c0019-1d96-47ab-ae7b-ad1b27fd512a)
![Screenshot from 2024-11-13 22-21-37](https://github.com/user-attachments/assets/c7e6f656-e73c-46a0-84b4-0b7d66c6e7e6)

80% Screenshots:
![image](https://github.com/user-attachments/assets/46d6a38e-99f0-4f39-92a4-a15dea7b27a3)
![image](https://github.com/user-attachments/assets/f4ab0100-0c70-4f9c-aaca-3b164b2e0789)

50% Screenshots:
![image](https://github.com/user-attachments/assets/1284c62a-0067-45f1-bcf2-a476829fc266)
![image](https://github.com/user-attachments/assets/afbfaf7a-7692-4ec1-9c0b-c4cd0eb4282a)




```
Rise Transition : 2.24638 - 2.18242 =  0.06396 ns = 63.96 ps
Fall Transition : 4.0955 - 4.05536 =  0.0419 ns = 41.9 ps
Cell Rise Delay : 2.21144 - 2.15008 = 0.06136 ns = 61.36 ps
Cell Fall Delay : 4.07807 - 4.05 =0.02 ns = 20 ps
```

Magic Tool options and DRC Rules:

Now, go to home directory and run the below commands:

```
cd
wget http://opencircuitdesign.com/open_pdks/archive/drc_tests.tgz
tar xfz drc_tests.tgz
cd drc_tests
ls -al
gvim .magicrc
magic -d XR &
```

![image](https://github.com/user-attachments/assets/ec309dde-2de1-4069-87db-a9476a6ec03e)


First load the poly file by load poly.mag on tkcon window.

![image](https://github.com/user-attachments/assets/0bdb8a9c-b087-4606-9980-7fce0152b870)


We can see that Poly.9 is incorrect.

The Poly rules can be seen here:

![image](https://github.com/user-attachments/assets/c4ae9a60-be7c-4840-99e6-5c21aaa460f1)


Add the below commands in the sky130A.tech

![image](https://github.com/user-attachments/assets/9fa3d7be-53a5-4f77-a5aa-eefa64e933af)

![image](https://github.com/user-attachments/assets/9f9f5052-f4e9-42b0-b5bf-1d92b6b3c3e4)


Run the commands in tkcon window:

```
tech load sky130A.tech
drc check
drc why
```

![image](https://github.com/user-attachments/assets/2dd525a3-50a5-490d-b843-fbd5aeca6e08)

</details>
<details>
<summary>Day-4</summary>
<br>
	
### Pre-layout timing analysis and importance of good clock tree

Commands to extract `tracks.info` file:

```
cd Desktop/work/tools/openlane_working_dir/openlane/vsdstdcelldesign
cd ../../pdks/sky130A/libs.tech/openlane/sky130_fd_sc_hd/
less tracks.info
```

![image](https://github.com/user-attachments/assets/6e0cfb41-80f6-4abf-99f6-1c5230161cf4)

Commands for tkcon window to set grid as tracks of locali layer

```
grid 0.46um 0.34um 0.23um 0.17um
```

![image](https://github.com/user-attachments/assets/202c84c1-ebea-49a4-b0eb-a9960f3e4ddd)

Condition 1 verified:
![image](https://github.com/user-attachments/assets/db7446b9-f1b1-480e-af15-c9aab4d0a24b)

Condition 2 verified:

```
Horizontal Track Pitch = 0.46um
Width of the standard cell = 3 * 0.46 = 1.38um

```
![image](https://github.com/user-attachments/assets/abbd0ba2-b56b-46f9-b965-a7d9a98e1998)

Condition 3 verified:

```
Veritical Track Pitch = 0.34um
Length of the standard cell = 8 * 0.34 = 2.72um
```

![image](https://github.com/user-attachments/assets/205da43a-a9c5-40de-aece-25dfee3afb66)


![image](https://github.com/user-attachments/assets/ba8ed4c1-1e08-4b68-8182-d764f14198ee)



The grids show where the routing for the local-interconnet layer can only happen, the distance of the grid lines are the required pitch of the wire. Below, we can see that the guidelines are satisfied:



Now, save it by giving a custon name

```
save sky130_chiinv.mag
```

![image](https://github.com/user-attachments/assets/f732b164-d33f-487f-a46b-3c1d03de28ad)



Now, open it by using the following commands:

```
magic -T sky130A.tech sky130_chiinv.mag &
```

![image](https://github.com/user-attachments/assets/ecb09169-6212-49fd-879d-c201fd2803a2)

![image](https://github.com/user-attachments/assets/841c2253-da8a-409a-97e9-254cc1931df1)



Now, type the following command in tkcon window:

```
lef write
```
![image](https://github.com/user-attachments/assets/81cdcdf0-1be8-4be5-8cb4-282f8a90cd72)


```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a
gedit config.tcl
```

Modify config.tcl:

```
# Design
set ::env(DESIGN_NAME) "picorv32a"

set ::env(VERILOG_FILES) "./designs/picorv32a/src/picorv32a.v"
set ::env(SDC_FILES) "./designs/picorv32a/src/picorv32a.sdc"


set ::env(CLOCK_PERIOD) "5.000"
set ::env(CLOCK_PORT) "clk"

set ::env(CLOCK_NET) $::env(CLOCK_PORT) 


set ::env(LIB_SYNTH) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__typical.lib "
set ::env(LIB_FASTEST) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__fast.lib"
set ::env(LIB_SLOWEST) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__slow.lib "
set ::env(LIB_TYPICAL) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__typical.lib"

set ::env(EXTRA_LEFS) [glob $::env(OPENLANE_ROOT)/designs/$::env(DESIGN_NAME)/src/*.lef]   ## this is the new line added to the existing config.tcl file

set filename $::env(OPENLANE_ROOT)/designs/$::env(DESIGN_NAME)/$::env(PDK)_$::env(STD_CELL_LIBRARY)_config.tcl
if { [file exists $filename] == 1 } {
  source $filename
}
```
![image](https://github.com/user-attachments/assets/926c8581-b837-4a97-b34b-19a0f453892e)


Copy the newly generated lef and associated required lib files to 'picorv32a' design 'src' directory.

```
# Copy lef file
cp sky130_vsdinv.lef ~/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/

# List and check whether it's copied
ls ~/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/

# Copy lib files
cp libs/sky130_fd_sc_hd__* ~/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/

# List and check whether it's copied
ls ~/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/
```

Now, run openlane flow synthesis:

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
```

```
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
run_synthesis
```
![image](https://github.com/user-attachments/assets/f6dbf40d-b6f7-4bd9-a1fd-b5497d70a2d9)

![image](https://github.com/user-attachments/assets/a182280a-bd58-414c-8e43-35fa03535890)

![image](https://github.com/user-attachments/assets/3b33b0bb-2bae-4bbd-844f-e019349e7d07)
![image](https://github.com/user-attachments/assets/875bff1b-5bb3-4359-9dc9-5504f5225736)

![image](https://github.com/user-attachments/assets/e7b26f65-3fc8-4fd7-a2ce-7c1c63ed3174)


**Delay Tables**

Delay plays a crucial role in cell timing, impacted by input transition and output load. Cells of the same type can have different delays depending on wire length due to resistance and capacitance variations. To manage this, "delay tables" are created, using 2D arrays with input slew and load capacitance for each buffer size as timing models. Algorithms compute buffer delays from these tables, interpolating where exact data isn’t available to estimate delays accurately, preserving signal integrity across varying load conditions.

![image](https://github.com/user-attachments/assets/095a59e1-158c-4870-88e3-b73cb3a3692c)

Fixing slack:

```
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a -tag 24-03_10-03 -overwrite
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
echo $::env(SYNTH_STRATEGY)
set ::env(SYNTH_STRATEGY) "DELAY 3"
echo $::env(SYNTH_BUFFERING
echo $::env(SYNTH_SIZING)
set ::env(SYNTH_SIZING) 1
echo $::env(SYNTH_DRIVING_CELL)
run_synthesis
```

![image](https://github.com/user-attachments/assets/cc9a9100-7626-443d-9785-b22d00f0bcd1)

![image](https://github.com/user-attachments/assets/32625a97-80e6-4925-8709-6c51763dfcb9)

![image](https://github.com/user-attachments/assets/082c9d5a-fde0-42f1-83d8-1a4a23bba542)


Now, run floorplan

```
run_floorplan
```
![image](https://github.com/user-attachments/assets/144d67d9-d775-4024-bbf8-258706b4058f)

![image](https://github.com/user-attachments/assets/d4b202ae-5469-4b42-aa08-006f1f882edf)


Since we are facing unexpected un-explainable error while using run_floorplan command, we can instead use the following set of commands available based on information from `Desktop/work/tools/openlane_working_dir/openlane/scripts/tcl_commands/floorplan.tcl` and also based on Floorplan Commands section in `Desktop/work/tools/openlane_working_dir/openlane/docs/source/OpenLANE_commands.md`

```
init_floorplan
place_io
tap_decap_or
```
![image](https://github.com/user-attachments/assets/3c078305-d12b-4532-91d0-8c70957cbf90)



Now, do placement

```
run_placement
```

![image](https://github.com/user-attachments/assets/e8ad32e9-0f9c-4925-a57a-f15683695918)

![image](https://github.com/user-attachments/assets/7f45b065-6b76-47ac-9e29-bae6a514721a)

Now, open a new terminal and run the below commands to load placement def in magic

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/24-03_10-03/results/placement/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.placement.def &

```

![image](https://github.com/user-attachments/assets/6180b6e4-ee06-4e16-a787-fa77e9f5f8c3)


Custom inverter inserted in placement def

![image](https://github.com/user-attachments/assets/c4124f73-3328-4ef8-b3f8-af7336874f63)


Now, select the cell and type `expand` in tkcon window to view internal layers of cells

![image](https://github.com/user-attachments/assets/ab793e39-8ca8-4d88-9e2d-bb8d8a09b6ee)


**Timing analysis with ideal clocks using openSTA**

Pre-layout STA will include effects of clock buffers and net-delay due to RC parasitics (wire delay will be derived from PDK library wire model).

![image](https://github.com/user-attachments/assets/a74af227-70dd-4812-930d-b6e9e787a27f)

Since we are getting 0 wns after improved timing run, we will be doing the timing analysis on initial run of synthesis which has lots of violations and no parameters added to improve timing.

Commands to invoke the OpenLANE flow include new lef and perform synthesis:

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
./flow.tcl -interactive
package require openlane 0.9set
prep -design picorv32a
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
set ::env(SYNTH_SIZING) 1
run_synthesis
```

![image](https://github.com/user-attachments/assets/53e63456-156d-4095-96f8-5ac41f88f4d0)


Go, to `Desktop/work/tools/openlane_working_dir/openlane` and create a file `pre_sta.conf`. The contents of the file are:

```
set_cmd_units -time ns -capacitance pF -current mA -voltage V -resistance kOhm -distance um
read_liberty -max /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/sky130_fd_sc_hd__slow.lib
read_liberty -min /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/sky130_fd_sc_hd__fast.lib
read_verilog /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/24-03_10-03/results/synthesis/picorv32a.synthesis.v
link_design picorv32a
read_sdc /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/my_base.sdc
report_checks -path_delay min_max -fields {slew trans net cap input_pin}
report_tns
report_wns
```

Contents of `my_base.sdc`:

```
set ::env(CLOCK_PORT) clk
set ::env(CLOCK_PERIOD) 12.000
set ::env(SYNTH_DRIVING_CELL) sky130_fd_sc_hd__inv_8
set ::env(SYNTH_DRIVING_CELL_PIN) Y
set ::env(SYNTH_CAP_LOAD) 17.65
create_clock [get_ports $::env(CLOCK_PORT)]  -name $::env(CLOCK_PORT)  -period $::env(CLOCK_PERIOD)
set IO_PCT  0.2
set input_delay_value [expr $::env(CLOCK_PERIOD) * $IO_PCT]
set output_delay_value [expr $::env(CLOCK_PERIOD) * $IO_PCT]
puts "\[INFO\]: Setting output delay to: $output_delay_value"
puts "\[INFO\]: Setting input delay to: $input_delay_value"


set clk_indx [lsearch [all_inputs] [get_port $::env(CLOCK_PORT)]]
#set rst_indx [lsearch [all_inputs] [get_port resetn]]
set all_inputs_wo_clk [lreplace [all_inputs] $clk_indx $clk_indx]
#set all_inputs_wo_clk_rst [lreplace $all_inputs_wo_clk $rst_indx $rst_indx]
set all_inputs_wo_clk_rst $all_inputs_wo_clk


# correct resetn
set_input_delay $input_delay_value  -clock [get_clocks $::env(CLOCK_PORT)] $all_inputs_wo_clk_rst
#set_input_delay 0.0 -clock [get_clocks $::env(CLOCK_PORT)] {resetn}
set_output_delay $output_delay_value  -clock [get_clocks $::env(CLOCK_PORT)] [all_outputs]

# TODO set this as parameter
set_driving_cell -lib_cell $::env(SYNTH_DRIVING_CELL) -pin $::env(SYNTH_DRIVING_CELL_PIN) [all_inputs]
set cap_load [expr $::env(SYNTH_CAP_LOAD) / 1000.0]
puts "\[INFO\]: Setting load to: $cap_load"
set_load  $cap_load [all_outputs]
```

Commands to run STA:

```
cd Desktop/work/tools/openlane_working_dir/openlane
sta pre_sta.conf
```

![image](https://github.com/user-attachments/assets/1a54a342-ed2a-4d96-b2e0-000f1b2e1f66)

![image](https://github.com/user-attachments/assets/57b25588-ef75-4d07-ae5a-b30174752250)

We now try to optimise synthesis.

Go to new terminal and run the following commands:

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
./flow.tcl -interactive
prep -design picorv32a -tag 25-03_18-52 -overwrite
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
set ::env(SYNTH_SIZING) 1
set ::env(SYNTH_MAX_FANOUT) 4
echo $::env(SYNTH_DRIVING_CELL)
run_synthesis
```

![image](https://github.com/user-attachments/assets/4cc9504f-4de0-4c81-aaf5-7025578d3f3c)

![image](https://github.com/user-attachments/assets/a898e02a-b1bb-4c5b-889a-217204acf123)

Commands to run STA:

```
cd Desktop/work/tools/openlane_working_dir/openlane
sta pre_sta.conf
```

![image](https://github.com/user-attachments/assets/448a6117-6c9e-457a-96cc-68f82ee7cfdf)

![image](https://github.com/user-attachments/assets/1ae7b1c8-8b13-4b59-91ca-2de1372addd0)


**Basic timing ECO**

NOR gate of drive strength 2 is driving 5 fanouts

![image](https://github.com/user-attachments/assets/73fdc61e-40d1-4496-9a05-2737556b9064)


Run the following commands to optimise timing:

```
report_net -connections _13295_
replace_cell _16155_ sky130_fd_sc_hd__nor3_4
report_checks -fields {net cap slew input_pins} -digits 4
```

![image](https://github.com/user-attachments/assets/11d5e71b-6be9-415e-864f-bde0da3c39b0)

![image](https://github.com/user-attachments/assets/4efdb86c-0614-4880-8139-577eab8bfc5d)


We can observe that the tns has reduced to -402.10 from -403.54 and wns has reduced to -5.38 from -5.59

**Clock tree synthesis TritonCTS and signal integrity**

Clock Tree Synthesis (CTS) techniques vary based on design needs:

- Balanced Tree CTS: Uses a balanced binary-like tree for equal path lengths, minimizing clock skew but with moderate power efficiency.
- H-tree CTS: Employs an "H"-shaped structure, good for large areas and power efficiency.

   ![image](https://github.com/user-attachments/assets/d1b13f19-a87f-41b6-8f29-a4e00a8e7216)

- Star CTS: Distributes the clock from a central point, minimizing skew but requiring more buffers near the source.
- Global-Local CTS: Combines star and tree topologies, with a global tree for clock domains and local trees within domains, balancing global and local timing.
- Mesh CTS: Uses a grid pattern ideal for structured designs, balancing simplicity and skew.
- Adaptive CTS: Dynamically adjusts based on timing and congestion, offering flexibility but with added complexity.

**Crosstalk**

Crosstalk is interference from overlapping electromagnetic fields between adjacent circuits, causing unwanted signals. In VLSI, it can lead to data corruption, timing issues, and higher power consumption. Mitigation strategies include optimized layout and routing, shielding, and clock gating to reduce dynamic power and minimize crosstalk effects.

![image](https://github.com/user-attachments/assets/21df4ac0-57aa-492e-adfa-7e04ce385680)

**Clock Net Shielding**

Clock net shielding prevents glitches by isolating the clock network, using shields connected to VDD or GND that don’t switch. It reduces interference by isolating clocks from other signals, often with dedicated routing layers and clock buffers. Additionally, clock domain isolation helps prevent cross-domain interference, avoiding metastability and maintaining synchronization.

![image](https://github.com/user-attachments/assets/bf85dd84-dc29-4962-877a-ce4f535bab2c)

Now to insert this updated netlist to PnR flow and we can use write_verilog and overwrite the synthesis netlist but before that we are going to make a copy of the old old netlist:

Run the following commands:

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/25-03_18-52/results/synthesis/
ls
cp picorv32a.synthesis.v picorv32a.synthesis_old.v
ls
```

Commands to write verilog:

```
write_verilog /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/25-03_18-52/results/synthesis/picorv32a.synthesis.v
exit
```
Verified that the netlist is overwritten

![image](https://github.com/user-attachments/assets/463de151-df01-4ba6-bc03-00c3785932fd)


Now, run the following commands:

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
./flow.tcl -interactive
prep -design picorv32a -tag 25-03_18-52 -overwrite
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
set ::env(SYNTH_STRATEGY) "DELAY 3"
set ::env(SYNTH_SIZING) 1
run_synthesis
init_floorplan
place_io
tap_decap_or
run_placement
run_cts
```
![image](https://github.com/user-attachments/assets/9e2f473c-afb3-464d-8e03-26c13a80b46c)
![image](https://github.com/user-attachments/assets/2379cf3b-4e6a-40d0-8c28-41db83c8cfb6)

The placement & cts is succesfull as shown below:
![image](https://github.com/user-attachments/assets/9ec8869f-19bc-443e-aff5-69c1c750aed0)

![image](https://github.com/user-attachments/assets/8b612dc6-37c9-48ac-8596-6fb6edfbd774)
![image](https://github.com/user-attachments/assets/c74f87eb-c7eb-46d3-a78e-b4b34013d1ea)



**Setup timing analysis using real clocks**

A real clock in timing analysis accounts for practical factors like clock skew and clock jitter. Clock skew is the difference in arrival times of the clock signal at different parts of the circuit due to physical delays, which affects setup and hold timing margins. Clock jitter is the variability in the clock period caused by power, temperature, and noise fluctuations, leading to uncertainty in clock edge timing. Both factors are crucial for accurate timing analysis, ensuring the design performs reliably in real-world conditions.

![image](https://github.com/user-attachments/assets/3526c927-e1a9-445a-9dae-22bc7e0446c7)

![image](https://github.com/user-attachments/assets/0c766405-5f9b-4700-a4cd-6fd19e9ea6cc)

Now, enter the following commands for Post-CTS OpenROAD timing analysis:

```
openroad
read_lef /openLANE_flow/designs/picorv32a/runs/25-03_18-52/tmp/merged.lef
read_def /openLANE_flow/designs/picorv32a/runs/25-03_18-52/results/cts/picorv32a.cts.def
write_db pico_cts.db
read_db pico_cts.db
read_verilog /openLANE_flow/designs/picorv32a/runs/25-03_18-52/results/synthesis/picorv32a.synthesis_cts.v
read_liberty $::env(LIB_SYNTH_COMPLETE)
link_design picorv32a
read_sdc /openLANE_flow/designs/picorv32a/src/my_base.sdc
set_propagated_clock [all_clocks]
report_checks -path_delay min_max -fields {slew trans net cap input_pins} -format full_clock_expanded -digits 4
exit
```

![image](https://github.com/user-attachments/assets/b73ef414-6669-420d-9cd7-273a2605ba30)

![image](https://github.com/user-attachments/assets/a329908f-59ad-48ed-99a1-51dd4a591dcb)

![image](https://github.com/user-attachments/assets/cb125b21-5688-4a63-9fe3-d7c1e5f99218)

![image](https://github.com/user-attachments/assets/df5b369f-47bd-42bc-a700-7a1608fe9f73)



Now, enter the following commands for exploring post-CTS OpenROAD timing analysis by removing 'sky130_fd_sc_hd__clkbuf_1' cell from clock buffer list variable 'CTS_CLK_BUFFER_LIST':

```
echo $::env(CTS_CLK_BUFFER_LIST)
set ::env(CTS_CLK_BUFFER_LIST) [lreplace $::env(CTS_CLK_BUFFER_LIST) 0 0]
echo $::env(CTS_CLK_BUFFER_LIST)
echo $::env(CURRENT_DEF)
set ::env(CURRENT_DEF) /openLANE_flow/designs/picorv32a/runs/25-03_18-52/results/placement/picorv32a.placement.def
run_cts
echo $::env(CTS_CLK_BUFFER_LIST)
openroad
read_lef /openLANE_flow/designs/picorv32a/runs/25-03_18-52/tmp/merged.lef
read_def /openLANE_flow/designs/picorv32a/runs/25-03_18-52/results/cts/picorv32a.cts.def
write_db pico_cts1.db
read_db pico_cts.db
read_verilog /openLANE_flow/designs/picorv32a/runs/25-03_18-52/results/synthesis/picorv32a.synthesis_cts.v
read_liberty $::env(LIB_SYNTH_COMPLETE)
link_design picorv32a
read_sdc /openLANE_flow/designs/picorv32a/src/my_base.sdc
set_propagated_clock [all_clocks]
report_checks -path_delay min_max -fields {slew transd net cap input_pins} -format full_clock_expanded -digits 4
report_clock_skew -hold
report_clock_skew -setup
exit
echo $::env(CTS_CLK_BUFFER_LIST)
set ::env(CTS_CLK_BUFFER_LIST) [linsert $::env(CTS_CLK_BUFFER_LIST) 0 sky130_fd_sc_hd__clkbuf_1]
echo $::env(CTS_CLK_BUFFER_LIST)
```

![image](https://github.com/user-attachments/assets/e59766d3-9368-4f61-b2a8-bc84a49a4449)

![image](https://github.com/user-attachments/assets/f37c80ea-9423-4de9-947a-62a547dea373)

![image](https://github.com/user-attachments/assets/c1a143d5-95a9-4bb2-8544-137fee15f607)

![image](https://github.com/user-attachments/assets/db87f93a-27d0-477c-b687-14ee93f53be2)

![image](https://github.com/user-attachments/assets/e27eb812-4972-4daa-8797-0b51430268bb)
</details>

<details>
<summary>Day-5 </summary>
<br>
	
### Final steps for RTL2GDS using tritonRoute and openSTA
	
#  Maze Routing and Lee's algorithm

 Routing is the process of establishing a physical connection between two pins. Algorithms designed for routing take source and target pins and aim to find the most efficient path between them, ensuring a valid connection exists.

The Maze Routing algorithm, such as the Lee algorithm, is one approach for solving routing problems. In this method, a grid similar to the one created during cell customization is utilized for routing purposes. The Lee algorithm starts with two designated points, the source and target, and leverages the routing grid to identify the shortest or optimal route between them.

The algorithm assigns labels to neighboring grid cells around the source, incrementing them from 1 until it reaches the target (for instance, from 1 to 7). Various paths may emerge during this process, including L-shaped and zigzag-shaped routes. The Lee algorithm prioritizes selecting the best path, typically favoring L-shaped routes over zigzags. If no L-shaped paths are available, it may resort to zigzag routes. This approach is particularly valuable for global routing tasks.

However, the Lee algorithm has limitations. It essentially constructs a maze and then numbers its cells from the source to the target. While effective for routing between two pins, it can be time-consuming when dealing with millions of pins. There are alternative algorithms that address similar routing challenges.

![image](https://github.com/user-attachments/assets/417076b5-915d-45d3-8935-1ff0e05b2e35)

## Design Rule Check (DRC)

DRC verifies whether a design meets the predefined process technology rules given by the foundry for its manufacturing. DRC checking is an essential part of the physical design flow and ensures the design meets manufacturing requirements and will not result in a chip failure. It defines the Quality of chip. They are so many DRCs, let us see few of them

Design rules for physical wires

Minimum width of the wire, Minimum spacing between the wires, Minimum pitch of the wire To solve signal short violation, we take the metal layer and put it on to upper metal layer. we check via rules, Via width, via spacing.

## Power Distribution Network generation

Unlike the general ASIC flow, Power Distribution Network generation is not a part of floorplan run in OpenLANE. PDN must be generated after CTS and post-CTS STA analyses:

we can check whether PDN has been created or no by check the current def environment variable: ``` echo $::env(CURRENT_DEF)```

```
prep -design picorv32a -tag Run 13-11_00-51
gen_pdn

```


- Once the command is given, power distribution netwrok is generated.
- The power distribution network has to take the ```design_cts.def``` as the input def file.
- Power rings,strapes and rails are created by PDN.
- From VDD and VSS pads, power is drawn to power rings.
- Next, the horizontal and vertical strapes connected to rings draw the power from strapes.
- Stapes are connected to rings and these rings are connected to std cells. So, standard cells get power from rails.
- The standard cells are designed such that it's height is multiples of the vertical tracks /track pitch.Here, the pitch is 2.72. Only if the above conditions are adhered it is possible to power the standard cells.
- There are definitions for the straps and the rails. In this design, straps are at metal layer 4 and 5 and the standard cell rails are at the metal layer 1. Vias connect accross the layers as required.

![image](https://github.com/user-attachments/assets/30a07831-821e-490d-9187-32ff901060dc)

## Routing

 In the realm of routing within Electronic Design Automation (EDA) tools, such as both OpenLANE and commercial EDA tools, the routing process is exceptionally intricate due to the vast design space. To simplify this complexity, the routing procedure is typically divided into two distinct stages: Global Routing and Detailed Routing.

The two routing engines responsible for handling these two stages are as follows:

- **Global Routing**: In this stage, the routing region is subdivided into rectangular grid cells and represented as a coarse 3D routing graph. This task is accomplished by the "FASTE ROUTE" engine.

- **Detailed Routing**: Here, finer grid granularity and routing guides are employed to implement the physical wiring. The "tritonRoute" engine comes into play at this stage. "Fast Route" generates initial routing guides, while "Triton Route" utilizes the Global Route information and further refines the routing, employing various strategies and optimizations to determine the most optimal path for connecting the pins.

## Key Features of TritonRoute

- **Initial Detail Routing**: TritonRoute initiates the detailed routing process, providing the foundation for the subsequent routing steps.

- **Adherence to Pre-Processed Route Guides**: TritonRoute places significant emphasis on following pre-processed route guides. This involves several actions:

   - **Initial Route Guide Analysis**: TritonRoute analyzes the directions specified in the preferred route guides. If any non-directional routing guides are identified, it breaks them down into unit widths.

   - **Guide Splitting**: In cases where non-directional routing guides are encountered, TritonRoute divides them into unit widths to facilitate routing.

   - **Guide Merging**: TritonRoute merges guides that are orthogonal (touching guides) to the preferred guides, streamlining the routing process.

   - **Guide Bridging**: When it encounters guides that run parallel to the preferred routing guides, TritonRoute employs an additional layer to bridge them, ensuring efficient routing within the preprocessed guides.
   - Assumes route guide for each net satisfy inter guide connectivity Same metal layer with touching guides or neighbouring metal layers with nonzero  vertically overlapped area( via are placed ).each unconnected termial i.e., pin of a standard cell instance should have its pin shape overlapped by a routing guide( a black dot(pin) with purple box(metal1 layer)). 


In summary, TritonRoute is a sophisticated tool that not only performs initial detail routing but also places a strong emphasis on optimizing routing within pre-processed route guides by breaking down, merging, and bridging them as needed to achieve efficient and effective routing results.

Works on MILP(Mixed Integer linear programming) based panel routing scheme with Intra-layer parallel and Inter-layer sequential routing framework

# TritonRoute problem statement

```
Inputs : LEF, DEF, Preprocessed route guides
Output : Detailed routing solution with optimized wire length and via count
Constraints : Route guide honoring, connectivity constraints and design rules.

```
The space where the detailed route takes place has been defined. Now TritonRoute handles the connectivity in two ways.

Access Point(AP) : An on-grid point on the metal of the route guide, and is used to connect to lower-layer segments, pins or IO ports,upper-layer segments.
Access Point Cluster(APC) : A union of all the Aps derived from same lower-layer segment, a pin or an IO port, upper-layer guide.

**TritonRoute run for routing**

Make sure the CURRENT_DEF is set to pdn.def

Start routing by using

```
run_routing
```
The options for routing can be set in the config.tcl file.
The optimisations in routing can also be done by specifying the routing strategy to use different version of TritonRoute Engine. There is a trade0ff between the optimised route and the runtime for routing.

#### 1. Perform generation of Power Distribution Network (PDN) and explore the PDN layout.

Commands to perform all necessary stages up until now

```bash
# Change directory to openlane flow directory
cd Desktop/work/tools/openlane_working_dir/openlane

# alias docker='docker run -it -v $(pwd):/openLANE_flow -v $PDK_ROOT:$PDK_ROOT -e PDK_ROOT=$PDK_ROOT -u $(id -u $USER):$(id -g $USER) efabless/openlane:v0.21'
# Since we have aliased the long command to 'docker' we can invoke the OpenLANE flow docker sub-system by just running this command
docker
```
```tcl
# Now that we have entered the OpenLANE flow contained docker sub-system we can invoke the OpenLANE flow in the Interactive mode using the following command
./flow.tcl -interactive

# Now that OpenLANE flow is open we have to input the required packages for proper functionality of the OpenLANE flow
package require openlane 0.9

# Now the OpenLANE flow is ready to run any design and initially we have to prep the design creating some necessary files and directories for running a specific design which in our case is 'picorv32a'
prep -design picorv32a

# Addiitional commands to include newly added lef to openlane flow merged.lef
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs

# Command to set new value for SYNTH_STRATEGY
set ::env(SYNTH_STRATEGY) "DELAY 3"

# Command to set new value for SYNTH_SIZING
set ::env(SYNTH_SIZING) 1

# Now that the design is prepped and ready, we can run synthesis using following command
run_synthesis

# Following commands are alltogather sourced in "run_floorplan" command
init_floorplan
place_io
tap_decap_or

# Now we are ready to run placement
run_placement

# Incase getting error
unset ::env(LIB_CTS)

# With placement done we are now ready to run CTS
run_cts

# Now that CTS is done we can do power distribution network
gen_pdn 
```

Screenshots of power distribution network run
![image](https://github.com/user-attachments/assets/7466227e-9818-4111-aa8f-4e6b7294299f)
![image](https://github.com/user-attachments/assets/62433a25-3ab6-49a5-8a1a-b8040ca8cf43)
![image](https://github.com/user-attachments/assets/1a2b9859-30e4-4704-b9b5-15abd363b9f6)
![image](https://github.com/user-attachments/assets/86615d8f-489c-451e-b281-1bba33d08ad2)




Commands to load PDN def in magic in another terminal

```bash
# Change directory to path containing generated PDN def
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_23-30/tmp/floorplan/

# Command to load the PDN def in magic tool
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read 14-pdn.def &
```

Screenshots of PDN def
![image](https://github.com/user-attachments/assets/28192d88-8a24-4de3-943d-a3500f4affb3)

![image](https://github.com/user-attachments/assets/637cba6d-53fd-4026-909c-ace3ef545246)

![image](https://github.com/user-attachments/assets/583a921e-41e2-485f-a73c-6955352a3b88)

![image](https://github.com/user-attachments/assets/d1b3fe38-e83a-4a41-a832-2616f6f68455)


#### 2. Perfrom detailed routing using TritonRoute and explore the routed layout.

Command to perform routing

```
# Check value of 'CURRENT_DEF'
echo $::env(CURRENT_DEF)

# Check value of 'ROUTING_STRATEGY'
echo $::env(ROUTING_STRATEGY)

# Command for detailed route using TritonRoute
run_routing
```

Screenshots of routing run

![image](https://github.com/user-attachments/assets/c95c231e-1b26-4fca-be59-9acdab09d442)

![image](https://github.com/user-attachments/assets/d8527849-e1d4-46bc-b913-227f83577a6f)

![image](https://github.com/user-attachments/assets/61b46b27-86c9-4d21-8f0f-525ae4774fb3)

![image](https://github.com/user-attachments/assets/459704ff-adc8-4686-87e6-816a85de8d6e)

![image](https://github.com/user-attachments/assets/b5a813d6-4297-4148-a4a1-d3a9cbb2a9e2)

Commands to load routed def in magic in another terminal

```bash
# Change directory to path containing routed def
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_00-51/results/routing/

# Command to load the routed def in magic tool
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.def &
```

Screenshots of routed def

![image](https://github.com/user-attachments/assets/7346af00-383e-47b9-a15f-1f71d049d294)

![image](https://github.com/user-attachments/assets/5e9d3f01-3a87-40a0-8d93-d29d6f36ef2f)


![image](https://github.com/user-attachments/assets/15668009-70ea-466a-a0be-47019ea05fd6)




Screenshot of fast route guide present in `openlane/designs/picorv32a/runs/13-11_00-51/tmp/routing` directory

![image](https://github.com/user-attachments/assets/dde3e6ac-7a66-43fe-9f27-0798ca760ae9)


#### 3. Post-Route OpenSTA timing analysis with the extracted parasitics of the route.

Commands to be run in OpenLANE flow to do OpenROAD timing analysis with integrated OpenSTA in OpenROAD

```
# Command to run OpenROAD tool
openroad

# Reading lef file
read_lef /openLANE_flow/designs/picorv32a/runs/13-11_00-51/tmp/merged.lef

# Reading def file
read_def /openLANE_flow/designs/picorv32a/runs/13-11_00-51/results/routing/picorv32a.def

# Creating an OpenROAD database to work with
write_db pico_route.db

# Loading the created database in OpenROAD
read_db pico_route.db

# Read netlist post CTS
read_verilog /openLANE_flow/designs/picorv32a/runs/13-11_00-51/results/synthesis/picorv32a.synthesis_preroute.v

# Read library for design
read_liberty $::env(LIB_SYNTH_COMPLETE)

# Link design and library
link_design picorv32a

# Read in the custom sdc we created
read_sdc /openLANE_flow/designs/picorv32a/src/my_base.sdc

# Setting all cloks as propagated clocks
set_propagated_clock [all_clocks]

# Read SPEF
read_spef /openLANE_flow/designs/picorv32a/runs/13-11_00-51/results/routing/picorv32a.spef

# Generating custom timing report
report_checks -path_delay min_max -fields {slew trans net cap input_pins} -format full_clock_expanded -digits 4

# Exit to OpenLANE flow
exit
```

Screenshots of commands run and timing report generated

![image](https://github.com/user-attachments/assets/b9f88141-ddc0-453e-acd3-34c1835a0007)

![image](https://github.com/user-attachments/assets/c04d1b98-e0f9-448b-a9ae-633393c222f5)

![image](https://github.com/user-attachments/assets/a8a07a55-f4ee-4db6-a237-1249662902bd)



</details>   

# ASSIGNMENT 6: Physical Design using OpenRoad

**1. FinFET Basics:**
Path to Zetta-Scale Computing

Introduction:

* **Bombe:** The Bombe was an electro-mechanical machine designed during World War II to decrypt German Enigma-encrypted messages. It was refined and built by Alan Turing and Gordon Welchman at Bletchley Park, UK. The Bombe systematically tested possible rotor settings of the Enigma machine by exploiting known plaintext patterns. Its logical operations helped narrow down the vast number of possible keys, significantly accelerating the decryption process. The Bombe played a critical role in the Allied war effort.

* **ENIAC (Electronic Numerical Integrator and Computer):** It was developed during World War II by John Presper Eckert and John Mauchly at the University of Pennsylvania, was the first general-purpose, fully electronic digital computer. Completed in 1945, it was designed to compute artillery firing tables for the U.S. Army. ENIAC used vacuum tubes instead of mechanical or electromechanical components. However, it lacked a stored-program capability, requiring manual reconfiguration for each new task. ENIAC demonstrated the immense potential of electronic computing for large-scale numerical problems.

* **EDVAC (Electronic Discrete Variable Automatic Computer):** EDVAC, also developed by Eckert and Mauchly with conceptual input from John von Neumann, was one of the first computers to implement the stored-program concept. Completed in 1949, EDVAC represented a significant improvement over ENIAC by using binary representation instead of decimal and storing both data and instructions in memory. This innovation simplified programming and laid the groundwork for the modern von Neumann architecture.

**50 Years of Microprocessor Trend Data:**

![image](https://github.com/user-attachments/assets/663e8079-4932-4856-ae71-222a6a40527a)

**The Key metrics are:**

**Transistors (Orange Triangles):** The number of transistors on a microprocessor chip (in thousands) has increased exponentially, following Moore's Law, which predicts a doubling approximately every two years. This growth enabled more complex and capable processors, reaching the range of billions of transistors by the 2020s.

**Single-Thread Performance (Blue Circles):** It is measured using SpecINT. It indicates the computational ability of a single processor core. Performance grew steadily due to improvements in architecture, instruction-level parallelism, and clock speeds, but the growth rate slowed post-2005 due to physical limitations like power and heat.

**Frequency (Green Diamonds):** Processor clock speed (in MHz) rose steadily until the early 2000s but then stagnated as increasing clock speeds became inefficient due to heat dissipation issues.

**Typical Power (Red Triangles):** Power consumption increased with transistor density and frequency, becoming a critical design challenge around the mid-2000s.

**Number of Logical Cores (Black Dots):** The transition to multi-core processors gained momentum in the mid-2000s as a response to the stagnation in single-thread performance. By increasing the number of cores, processors enabled more efficient parallel processing, leading to significant improvements in overall performance


**Path to zetta-scale computing**

![image](https://github.com/user-attachments/assets/e56e21c0-e51f-4a81-988b-d055e6c6647f)image



**Key Performance Levels**

1. Gigascale (10⁹ FLOPS): The starting point in 1984, marking the capability of early supercomputers.
2. Terascale (10¹² FLOPS): Achieved around 1997, a significant milestone where systems like Jaguar (Cray XT5) delivered teraflop performance with power consumption of 7 MW.
3. Petascale (10¹⁵ FLOPS): Achieved in 2008 with systems like Titan (Cray XK6) at 27 petaflops, consuming 9 MW. This milestone represents the era of petascale high-performance computing (HPC).
4. Exascale (10¹⁸ FLOPS): Reached by systems like Frontier (Cray Shasta) in 2021, delivering 1.5 exaflops using 4 AMD GPUs and 1 AMD CPU, consuming 29 MW of power. Exascale computing enables highly detailed simulations and large-scale AI workloads.
5. Zettascale (10²¹ FLOPS): Projected to be achieved by around 2035. At this scale, systems will handle unprecedented computational workloads, such as advanced climate modeling, AI, and large-scale simulations. Power consumption is estimated to range between 50-100 MW for a single zettascale machine.

**CMOS Evolution and Next-Gen Candidates**

![image](https://github.com/user-attachments/assets/b138fedc-ecdd-4207-8ee5-faf1ce11e4e7)


This diagram illustrates the evolving landscape of CMOS (Complementary Metal-Oxide-Semiconductor) technology and highlights emerging materials, structures, and processes being explored for next-generation semiconductor devices. These innovations aim to address the challenges of scaling CMOS technology down to the 1nm node and beyond.

**Channel Material**

*	Current Trends:
            Silicon (Si) is the primary material used for the channel in traditional CMOS transistors, with strained SiGe (Silicon-Germanium) being used in some high-performance applications to enhance carrier mobility.

*	Future Materials:
            2D materials such as MoS₂ (Molybdenum Disulfide) are being explored due to their potential for better electrical characteristics at smaller scales.
            Germanium (Ge) is gaining interest as it offers higher electron mobility, which could significantly boost transistor performance at small nodes.

**Patterning**

*	Current Techniques:
            Deep Ultraviolet (DUV) lithography is the most commonly used technique for defining transistor features, with ArF (Argon Fluoride) and KrF (Krypton Fluoride) lasers operating at different wavelengths.

*	Next-Gen:
            Extreme Ultraviolet (EUV) lithography is expected to be a key technology for sub-7nm nodes. High-NA (Numerical Aperture) EUV will further improve the resolution for even smaller transistor nodes, pushing the boundaries of Moore's Law.

**Gate Stack Material**

*	Current Materials:
            High-K metal gates (HKMG) are used in the gate stack of modern FETs to reduce gate leakage current and improve switching performance.

*	Next-Gen Candidates:
            NC-FET (Negative Capacitance FET): This is a promising transistor design that leverages ferroelectric materials to reduce power consumption by enabling lower voltage operation.
            TFET (Tunnel FET): TFETs use quantum tunneling to switch on and off, offering a significant reduction in power consumption compared to conventional FETs, especially for low-power applications.

**Interconnection Material**

*	Current Materials:
            Copper (Cu) is the primary material used for interconnects due to its low resistivity, which helps in minimizing power loss and delays in transistor connections.

*	Next-Gen Materials:
            Ruthenium (Ru) and Compound metals are being investigated for their potential to reduce resistance and improve performance in ultra-small transistors.
            Topological semi-metals may offer unique properties, such as lower resistivity and increased performance at the atomic scale.

**Device Structure**

*	Current Architectures:
            FinFET and planar transistors are used to maintain performance at smaller nodes. FinFETs, in particular, help improve control over short-channel effects by using a 3D structure.

*	Next-Gen Architectures:
            3DS-FET (3D Stacked FET): These are three-dimensional transistors where multiple layers of devices are stacked vertically, reducing footprint and improving performance.
            MBC-FET (Multi-Bridge Channel FET): This structure aims to enhance drive current by creating multiple channels within the same device.
            VFET (Vertical FET): VFETs utilize vertical channels to improve density and reduce power consumption.

**Design Co-Optimization**

*	DTCO (Design-Technology Co-Optimization):
            DTCO focuses on integrating new design techniques with advanced process technologies to maximize chip performance, often involving backside interconnects (BSI), where interconnections are made at the back of the wafer for improved signal integrity and reduced latency.

*	STCO (System-Technology Co-Optimization):
            This approach involves optimizing both the system architecture and the underlying technology. One example is the use of chiplets, which allow for modular, customized designs by integrating multiple smaller chips into one package, offering flexibility and reducing the complexity of scaling single-chip designs.

**FinFETs**

![image](https://github.com/user-attachments/assets/4b50ff18-aab0-4ac0-bb92-a5a52712fb43)


This diagram illustrates the evolution of transistor technology from planar to more advanced architectures like FinFET and Gate-All-Around (GAA):

*	Planar Transistor (Traditional):
        Early transistor design with a flat channel and gate structure.
        The gate controls the channel from one side only, leading to limited performance as scaling continues.

*	FinFET (2011):
        The channel is shaped like a vertical fin, allowing the gate to wrap around three sides of the channel.
        Provides better control over the channel, reducing leakage and improving performance at smaller sizes.

*	Gate-All-Around (GAA) Transistor (2025?):
        The gate completely surrounds the channel, typically implemented using stacked nanosheets or nanowires.
        Offers even better control over the channel compared to FinFET, allowing higher performance and efficiency with continued scaling.

Each step improves drive current capability and enhances control over the transistor's on/off states, critical for power efficiency and miniaturization in modern electronics.

Why FinFETs and Gate-All-Around Transistors?

![image](https://github.com/user-attachments/assets/febc2fa2-2898-430d-867b-4f7e8d79355d)


This diagram explains the advantages of FinFETs and Gate-All-Around (GAA) transistors compared to traditional planar structures:

**Planar Transistors:**

*	Challenges:
        Sub-channel leakage occurs where current leaks underneath the gate.
        Results in reduced efficiency.
        Increases power consumption.

*	FinFET Transistors:
        The gate wraps around the channel (fin) on three sides, providing better control over the channel.
        **Benefits:**
           - 	Reduces sub-threshold leakage.
           - 	Enhances drive current ((I_{ON})).
           - 	Allows a smaller transistor area while maintaining high performance.

*	Gate-All-Around (GAA) Transistors:
        The gate completely surrounds the channel, offering superior electrostatic control.
        **Advantages:**
            -	Improves short-channel performance by reducing drain capacitance and enhancing gate capacitance.
            -	Improves scaling efficiency as indicated by the formula (S \propto (1 + C_d / C_{ox})).
            -	Provides reduced sub-threshold slope and better performance at smaller scales.

*	Graph Comparison:
            -	Illustrates the performance advantages of FinFETs and GAA over planar transistors.
  	    -	Shows better efficiency and reduced sub-threshold slope as dimensions shrink.

![image](https://github.com/user-attachments/assets/2598f386-9ccf-455a-8744-987de8245c99)


**Reduced Leakage:** Tri-Gate transistors exhibit significantly lower leakage current compared to planar transistors at the same gate voltage. Lower leakage results in both reduced off-current at the same on-current and lower power dissipation.

**Higher Drive Current:** Tri-Gate transistors provide higher drive current compared to planar transistors at the same off-current. This results in improved circuit performance and greater efficiency in modern electronic applications.

**FEOL Innovations:**

FEOL refers to the initial stages of semiconductor manufacturing where the active devices (e.g., transistors) are built on the silicon wafer. It involves creating components such as transistors, capacitors, and isolation structures before metal interconnects are added. FEOL Innovations help drive Moore's Law forward by enabling smaller, more efficient, and more powerful transistors.

**CMOS Technology Inflection Points**

![image](https://github.com/user-attachments/assets/fb763b75-19f1-4dfd-9d52-4a7ec1bb0779)


**1. Dennard Scaling:**
-	States that power density remains constant as transistors shrink.
-	Initially allowed voltage scaling with smaller gate lengths, shown in the bottom-left graph.

**2. Technology Nodes and Innovations:**
       *	~1 µm ("End of Scaling"): Start of CMOS miniaturization.
       *	180 nm (Voltage Scaling): Start of drive voltage reduction.
       *	130 nm (Cu BEOL): Introduction of copper interconnects for better conductivity.
       *	90 nm (Uniaxial Strained Si NMOS): Strained silicon enhances electron mobility.
       *	65 nm (eSiGe CVD ULK): Embedded SiGe improves PMOS performance.
       *	45 nm (HK-first MG-last): High-k dielectrics and metal gates reduce leakage and improve gate control.
       *	32 nm (HKMG with Raised S/D NMOS): Advanced HKMG implementation and raised source/drain regions.

**2. SEM Images**

*	**Left Image:** Shows the cross-sectional view of a transistor structure with High-k materials and embedded SiGe (Silicon-Germanium).It has high-k dielectric and metal gates are used to improve performance. SiGe regions enhance PMOS performance by applying strain to the silicon channel.

*	**Right Image:** Demonstrates the raised source/drain (S/D) regions and gate channel in PMOS transistors at smaller nodes.

**3. Drive Voltage Scaling Graph (Bottom-left):** The graph shows the relationship between gate length (x-axis, logarithmic scale) and drive voltage (y-axis, logarithmic scale). The Ideal scaling behavior indicates that the voltage decreases linearly with shrinking gate length. Red and green markers show practical trends for low-power and high-performance devices, which deviate from ideal scaling due to challenges like leakage currents and increased power density.

![image](https://github.com/user-attachments/assets/2e8b56c7-cb3d-4eb4-977d-64bc6701d124)


**Key Technology Nodes and Innovations**

**1. 22 nm:**
        Introduction of FinFET (Tri-Gate) transistors, which reduce leakage and improve gate control.
        Use of self-aligned contacts (SAC) and copper interconnects (Co+Cu BEOL).

**2. 14 nm:**
        Transition to unidirectional metal routing for better density.
        Implementation of SADP (Self-Aligned Double Patterning) and SDB (Single Diffusion Break) for precise layout.

**3. 10 nm:**
        Adoption of advanced patterning techniques such as:
        -	SA-SDB (Self-Aligned SDB)
        -	LELELE (Litho-Etch-Litho-Etch-Litho-Etch)
        -	SAQP (Self-Aligned Quadruple Patterning) for tighter geometries.

**4. 7 nm:**
        -	Introduction of Extreme Ultraviolet Lithography (EUV) to simplify the patterning process and reduce overlay errors.

**5. 5 nm:**
        -	Integration of SiGe (Silicon-Germanium) channels for PMOS to enhance hole mobility.
        -	Use of EUV SA-LELE (Self-Aligned Litho-Etch-Litho-Etch).

**6. 3 nm / 2 nm / 1.4 nm:**
        -	Transition to Gate-All-Around (GAA) nanosheet transistors for improved electrostatic control.
        -	GAA stacks nanosheets or nanowires horizontally to maximize current drive.

**7. Sub-1 nm:**
        -	Development of CFET (Complementary FET), which vertically stacks NMOS over PMOS to save area.
        -	Use of 2D materials, such as MoS₂, for atomic-scale channel thickness in 2D FETs.

![image](https://github.com/user-attachments/assets/b0955ae3-73fe-441e-aa85-5e64bbbea3ce)


The image illustrates how Samsung has scaled down the size of transistors in their successive generations of nodes (10nm, 8nm, 7nm, and 5nm) using a technique called Fin Depopulation. In FinFET transistors, the "fin" is the vertical channel that carries the current. Fin Depopulation involves reducing the number of fins per transistor while keeping the fin width constant. This allows for smaller transistors without compromising performance.

    *	10nm (HD): The transistor has a fin height of 420nm and uses 10 fins.
    *	8nm (UHD): The fin height is reduced to 378nm, and the number of fins is decreased to 9.
    *	7nm (HD): The fin height remains at 27nm, but the number of fins is further reduced to 8.
    *	5nm (UHD): The fin height is maintained at 27nm, and the number of fins is decreased to 7.

![image](https://github.com/user-attachments/assets/06809cea-45b6-47c9-867c-4802faedf13e)


*	**Double Diffusion Break (DDB):** Double Diffusion Break (DDB) involves creating a gap between the source and drain regions of a transistor. This gap is filled with an insulating material, which reduces the effective width of the transistor. By doing so, DDB enables the design of smaller cell sizes, allowing for higher transistor density and improved scalability. A cross-sectional view of a transistor with DDB highlights the insulating gap between the source and drain regions.

*	**Single Diffusion Break (SDB):** Single Diffusion Break (SDB) is similar to DDB but less aggressive. It involves introducing a gap on only one side of the transistor. This approach provides a balanced trade-off between size reduction and maintaining transistor performance. A cross-section of a transistor with SDB highlights the gap on one side, showcasing its simplicity compared to DDB.

*	**Contact Over Field Gate (COFG):** Contact Over Field Gate (COFG) places the gate contact directly over the field oxide region of a transistor. This design reduces lateral spacing between adjacent transistors, enabling smaller cell sizes without significant performance loss. A cross-sectional representation of a transistor with COFG illustrates the positioning of the gate contact over the field oxide.

*	**Contact Over Active Gate (COAG):** Contact Over Active Gate (COAG) is a more aggressive technique than COFG. Here, the gate contact is placed directly over the active gate region of the transistor. This approach enables even smaller cell sizes and higher transistor density, which are critical for advanced semiconductor nodes. A cross-sectional image of a transistor with COAG highlights the gate contact placement over the active gate.

*	**Back-Side Power Delivery Network (BS-PDN):** The Back-Side Power Delivery Network (BS-PDN) is an innovative approach where power supply rails are routed on the backside of the chip. This method reduces the height of the standard cell, creating space for more transistors and improving overall transistor density. Additionally, it enhances power delivery efficiency and reduces resistance, which is crucial for high-performance applications. A schematic of a standard cell with BS-PDN illustrates the positioning of power rails on the backside of the chip.

![image](https://github.com/user-attachments/assets/b7a3fff3-158c-45ee-9f8d-cbc8638ae0d1)


*	**Planar Technology:** In early planar technology nodes (100nm and above), the Vt variability is significantly high, around 130mV. This is due to various factors like process variations, temperature fluctuations, and line-edge roughness.

*	**FinFET Technology:** With the advent of FinFET technology (around 22nm), the Vt variability reduces significantly to around 14mV. This improvement is attributed to the better control over the channel length and width in FinFETs compared to planar transistors.

*	**NW Technology (Nanowire):** In the latest nanowire technology (14nm and below), the Vt variability is even lower, around 7mV. This further reduction is due to the precise control over the nanowire dimensions and the reduced impact of process variations.

![image](https://github.com/user-attachments/assets/d52ffa2a-7dd3-4ed7-8486-8cf73fe02282)


**Planar MOSFETs**

Planar MOSFETs, the traditional architecture, have a simple structure where the gate sits above the channel. In this design, the contact width ((W_C)) and gate width ((W_G)) are nearly equal, resulting in a ratio of (W_C / W_G \approx 1). This leads to a low parasitic resistance, with (R_{EXT}) being much smaller than (R_{ch}) ((R_{EXT} / R_{ch} < 1)). As a result, planar MOSFETs suffer minimal performance degradation due to parasitic resistance.

**FinFETs**

FinFETs, a 3D transistor design, introduce vertical fins with the gate wrapping around them for improved control. However, the effective contact width decreases relative to the gate width, leading to (W_C / W_G \approx 1/3). Consequently, the parasitic resistance becomes comparable to the channel resistance ((R_{EXT} / R_{ch} \approx 1)), which begins to impact the performance of the device as it scales.

**Gate-All-Around (GAA) FETs**

Gate-All-Around (GAA) FETs, which use nanosheets or nanowires, offer even better electrostatic control by fully surrounding the channel with the gate. However, the contact width further decreases compared to the gate width, resulting in (W_C / W_G \approx 1/6). This causes a significant increase in parasitic resistance, with (R_{EXT}) being approximately three times the channel resistance ((R_{EXT} / R_{ch} \approx 3)). While GAA FETs improve transistor density, the higher parasitic resistance becomes a challenge for maintaining performance.

**Complementary FETs (CFETs)**

Complementary FETs (CFETs) take transistor stacking to the next level by vertically integrating NMOS and PMOS transistors. This approach maximizes space efficiency in advanced nodes but inherits the high parasitic resistance of GAA FETs. With (W_C / W_G) remaining small, the (R_{EXT} / R_{ch}) ratio is around 3, posing similar challenges to those faced by GAA FETs.

**Explanation of Parasitic Resistance**

![image](https://github.com/user-attachments/assets/f2d602b0-07b8-4a13-a55d-eb5fdd378ede)

The image highlights the breakdown of parasitic resistance ((R_{EXT})) and approaches for reducing it in transistors. Here is a detailed explanation:

Components of Parasitic Resistance ((R_{EXT})) The leftmost diagram illustrates the various contributors to (R_{EXT}) in a transistor:

    *	(R_{CA-BEOL}): Resistance from the contact in the Back-End-Of-Line (BEOL).
    *	(R_{CA}): Resistance at the contact area.
    *	(R_{CA-TS}): Resistance at the contact to the transition structure.
    *	(R_{TS}): Resistance in the transition structure.
    *	(R_{MOL}): Middle-Of-Line resistance (includes lateral and vertical contributions).
    *	(R_C): Contact resistance at the metal-semiconductor interface.
    *	(R_{EPI}): Epitaxial layer resistance (contributes to current spreading).
    *	(R_{FEOL}): Front-End-Of-Line resistance from the source/drain extensions.

Initial vs. Improved (R_{EXT}) Breakdown The two pie charts in the center show the contributions of different resistance components for NFETs and PFETs before and after improvements:

**NFET:**
        -	Initial: Majority of (R_{EXT}) comes from (R_C) (63%) and (R_{CA-BEOL}) (31%).
        -	Improved: Significant reduction in (R_C) (48%) and (R_{CA-BEOL}) (12%).
**PFET:**
        -	Initial: (R_{FEOL}) (50%) and (R_C) (45%) dominate.
        -	Improved: Major reduction in (R_{FEOL}) (78%) and (R_C) (16%).

Improving Ohmic/Tunneling Contacts The right section discusses methods to improve the metal-semiconductor interface:

**Key Objectives:**
        -	Low Schottky Barrier Height (SBH) ((\phi_b)): Reduces the energy barrier for carrier injection, enabling better contact conductivity.
        -	High Doping Concentration ((N_d)): Increases carrier density at the interface, reducing contact resistance.

Equation for Specific Contact Resistivity ((\rho_c)): [ \rho_c \propto \exp\left(\frac{2\phi_b}{\hbar} \sqrt{\frac{\epsilon_s m_x}{N_d}}\right) ] This equation shows how lowering (\phi_b) and increasing (N_d) can reduce (\rho_c).

**Metal-Semiconductor Energy Diagram:**
	The energy diagram shows how a reduction in (\phi_b) (Schottky Barrier Height) facilitates easier carrier injection from the metal to the semiconductor.

![image](https://github.com/user-attachments/assets/ba2911e6-0be6-4643-84b8-33745a16fbe7)


The bar chart on the left shows how the composition of (C_{eff}) evolves from 22nm to 7nm technology nodes:

*	At 22nm, the dominant contributor to (C_{eff}) is (C_{fr}) (56%), while parasitic capacitances (C_{pc-ca}) (25%) and (C_{g}) (19%) contribute less.
*	At 14nm and 10nm, parasitic capacitances ((C_{pc-ca}) and (C_{fr})) start dominating, with (C_{fr}) decreasing to 38% and 25%, respectively, while (C_{pc-ca}) increases.
*	At 7nm, (C_{g}) becomes the most significant contributor (45%), with (C_{pc-ca}) and (C_{fr}) still present but reduced. This highlights the increasing impact of parasitic capacitance as node sizes shrink.

**Plot Descriptions:**

*	The first scatter plot shows a reduction in normalized delay for a ring oscillator when using SiBCN spacers instead of SiN spacers, indicating improved performance.
*	The second scatter plot demonstrates an 8% reduction in (C_{eff}) with SiBCN spacers, which corresponds to the delay improvement observed in the first plot.
*	The rightmost figure shows the evolution of spacer materials from SiOCN to SiCO. This material transition aims to significantly reduce the gate-contact capacitance across nodes. At 14nm and beyond, low-(k) spacers improve performance by decoupling parasitic effects and maintaining capacitance at manageable levels.
*	The bottom middle image shows a cross-sectional TEM view of a transistor with air spacers around the gate: i) Air, with its extremely low dielectric constant ((k \approx 1)), significantly reduces parasitic capacitance. The adjacent plot quantifies this improvement, showing a 15% reduction in (C_{eff}) when using air spacers compared to solid spacers.

![image](https://github.com/user-attachments/assets/bb4fa79b-3767-40ca-a895-8ea4494ad8d9)


**Key Properties of 2D Layered Materials (Compared to Silicon):**

-	Uniform Atomic Scale Thickness: A single layer of MoS₂ is approximately 0.65 nm thick, offering an ideal thickness for scaling compared to silicon.
-	Higher Effective Mass (( m^ )):* MoS₂ has an effective mass of about 0.55 times the mass of a free electron (( m_0 )), whereas silicon’s effective mass is around 0.22 ( m_0 ).
-	Bandgap: Additionally, 2D materials like MoS₂ possess favorable bandgaps for electronic devices, with a monolayer bandgap of ~1.85 eV, which reduces to ~1.5 eV for a bilayer.

![image](https://github.com/user-attachments/assets/fd6b3e48-1998-461f-b54b-81b1a16aa0b4)

**Transistor Scaling:**
        To achieve smaller gate lengths, devices must address various physical and material constraints to ensure reliable operation.

**Challenges for Scaling:**
-	Direct Source-to-Drain Tunneling: As the gate length decreases, electrons can tunnel directly from the source to the drain, bypassing the gate control. To mitigate this, materials with a high effective mass (( m^* )) are needed.
-	Surface Roughness and Thickness Variations: Variability at atomic scales can cause performance issues. Uniform, atomically thin materials are essential for minimizing such variations.
-	Capacitance Ratios (( C_D ) and ( C_{ox} )): The capacitance of the depletion region (( C_D )) must remain low relative to the gate oxide capacitance (( C_{ox} )) to improve gate control. Materials with a low in-plane dielectric constant (( \epsilon )) are necessary for this.

**Diagrams:**
-	The left shows the transistor structure with key components like the source, drain, gate, oxide, and silicon substrate.
-	The right illustrates two scenarios:
        	a. Thermionic Emission: Electrons cross the energy barrier as intended.
        	b. Direct Tunneling: At extremely small gate lengths, electrons tunnel directly from source to drain, leading to leakage.

**Key Takeaway:**
        New channel materials, such as 2D materials, are required to overcome these challenges while maintaining high performance and scalability.

![image](https://github.com/user-attachments/assets/04001199-bb59-4efe-bf62-854e9ab07692)


Concept of Direct Source-to-Drain Tunneling: As the gate length ((L_G)) in MOSFETs decreases, direct tunneling of electrons from the source to the drain becomes significant, leading to increased leakage currents. This leakage is influenced by material properties, such as the effective mass ((m^*)) and the bandgap ((E_G)).

A higher (m^) in MoS₂ suppresses tunneling leakage compared to silicon. The graph shows the leakage current ((I_{SD, \text{leak}})) as a function of gate length ((L_G)) for various channel thicknesses ((T_{CH})). MoS₂ exhibits lower leakage at smaller gate lengths compared to silicon, achieving up to 100x reduction in leakage due to its higher (m^), larger (E_G), and lower dielectric constant ((\epsilon)).

The superior performance of MoS₂ in minimizing leakage currents results in significant energy savings, making it a promising material for future transistor scaling.

![image](https://github.com/user-attachments/assets/217727ce-441a-4aff-8af1-215451b3889d)


The MoS₂ transistor with a 1 nm gate length represents a breakthrough in miniaturization, featuring a thin MoS₂ channel for its excellent electronic properties. A single-walled carbon nanotube (SWCNT) serves as the ultra-small gate electrode, while Zirconium Dioxide (ZrO₂) acts as a high-k dielectric, reducing leakage and ensuring precise control. Built on a SiO₂ substrate with an n⁺ silicon back gate, the transistor uses the CNT gate to deplete a small region of the MoS₂ channel, enabling efficient modulation. This innovative design showcases the potential of 2D materials and nanoscale gates in advancing transistor technology.

![image](https://github.com/user-attachments/assets/4a685f55-49a0-4a9f-9fe1-68751dae440d)


The slide illustrates the structure and fabrication of an All-2D MOSFET (Metal-Oxide-Semiconductor Field-Effect Transistor), where all key components, including the channel, gate, and contacts, are made using two-dimensional materials. This device leverages the exceptional properties of 2D materials to improve performance and scalability. Below is a breakdown of the key components and the fabrication process:
*	Graphene Contacts (S, D, G): Graphene is used as the source, drain, and gate electrodes. Its high conductivity and 2D nature make it ideal for ensuring low-resistance electrical contacts. MoS₂ Channel:

*	Molybdenum Disulfide (MoS₂) serves as the semiconductor channel. MoS₂ is widely used in 2D MOSFETs due to its excellent on/off current ratio and atomic-scale thickness. h-BN Dielectric:

*	Hexagonal Boron Nitride (h-BN) acts as the insulating dielectric layer. It is a 2D material with excellent insulating properties and high thermal stability, making it suitable for separating the graphene gate from the MoS₂ channel. Si/SiO₂ Substrate:

The device is fabricated on a silicon dioxide (SiO₂) layer on top of a silicon substrate, which provides mechanical support and a global back gate. Fabrication Process:

*	A layer of graphene is deposited on the SiO₂ substrate, which will later serve as the gate electrode.
*	Graphene is patterned to define the source and drain regions, leaving gaps for the channel.
*	A monolayer of MoS₂ is transferred onto the patterned graphene, forming the channel region.
*	An h-BN layer is added on top of the MoS₂ as the gate dielectric.
*	A top layer of graphene is deposited and aligned as the gate electrode.
*	The completed device is contacted using metallic electrodes (Ni/Au) for testing.

![image](https://github.com/user-attachments/assets/2fc69f53-adba-4d11-99b1-2906b2745946)


**The All-2D MOSFET exhibits excellent electrical performance:**

*	Transfer Characteristics (I(_D) vs V(_G)): Achieves a high on/off current ratio (>10⁵), demonstrating strong gate control for effective switching.
*	Output Characteristics (I(D) vs V({DS})): Smooth current modulation with increasing V(G) and V({DS}), indicating good output performance.
*	Mobility: Field-effect mobility remains constant with increasing gate electric field, showing minimal scattering and high-quality interfaces in the 2D materials stack.

These results highlight the potential of 2D materials like MoS₂, graphene, and h-BN for scalable, high-performance transistor applications.

![image](https://github.com/user-attachments/assets/5e645878-5fc1-4e39-bbed-e7287002c676)


**The diagram on the top left shows a non-planar transistor with key components:**

*	Gate: Controls the flow of current through the channel.
*	Channel: Region where current flows between the source (S) and drain (D).
*	Body: Underlying region connected to the substrate.
*	STI (Shallow Trench Isolation): Insulates neighboring devices.

The biggest challenge is to form a single-crystalline semiconductors on a non-planar surface is difficult using conventional semiconductor fabrication techniques.

![image](https://github.com/user-attachments/assets/6299f7de-dcd6-4d0a-9996-5b389c879e9f)


**Single-Layer CMOS (a):**
	This is the traditional CMOS design where NMOS and PMOS transistors are fabricated on a single silicon layer. Each transistor operates in the same planar layer, with devices connected laterally.

**Monolithic 3D CMOS (b):**
	In this design, NMOS and PMOS transistors are stacked in two separate layers, enabling higher density. The P-Channel (PMOS) is placed on top of the N-Channel (NMOS), separated by an oxide layer. This approach reduces the footprint and allows better performance due to shorter interconnects.

**Single-Layer CMOS Logic (c):**	
	Shows logic gates (inverter, 2-input NAND, and 2-input NOR) built using traditional single-layer CMOS. Transistors are laid out horizontally, with interconnections taking more space.

**Monolithic 3D CMOS Logic (d):**
	Logic gates are constructed with two transistor layers (Layer 1 and Layer 2), reducing the area required for interconnections. Vertical integration improves performance and reduces delay by shortening signal paths.

![image](https://github.com/user-attachments/assets/8bd054cb-4827-4d0a-b0cc-b8a03d2ca775)



**2. Tool Installation:**

**Commands to install openroad:**
```
git clone --recursive https://github.com/The-OpenROAD-Project/OpenROAD-flow-scripts
cd OpenROAD-flow-scripts
sudo ./setup.sh
```

![Screenshot from 2024-11-26 00-58-53](https://github.com/user-attachments/assets/d65ea6fe-a7be-44d7-a51d-c4c2c9418896)



**Build tool on local machine command:**
```
./build_openroad.sh --local
```
![Screenshot from 2024-11-26 00-59-18](https://github.com/user-attachments/assets/30ceafd3-46e6-4c45-aa67-275ba8ef5acc)



**Verify Installation**:
```
source ./env.sh
yosys -help
openroad -help
cd flow
make
```

![Screenshot from 2024-11-26 01-13-04](https://github.com/user-attachments/assets/a48dae43-1f1c-416c-85b5-8d0e0f70bb8d)
![Screenshot from 2024-11-26 01-12-50](https://github.com/user-attachments/assets/69cd31e5-700d-463a-9e6a-6e59ede697ec)

```
make gui_final
```

![Screenshot from 2024-11-26 01-13-37](https://github.com/user-attachments/assets/0bb5b5ce-6bbe-428f-91e1-129c4af437a7)

![Screenshot from 2024-11-26 01-14-18](https://github.com/user-attachments/assets/b2fddd6e-a040-4497-9927-f8fe603ff260)


**3. Flow Structure:**

Physical Design Flow :

![image](https://github.com/user-attachments/assets/d56698f9-2dbb-4589-affa-468219542cc3)

Physical Design is the process of translating the gate level netlist into a physical layout. This physical layout consists of various metal shapes and sizes which can be drawn onto masks and manufactured on the silicon wafer.

The Physical Design process can be broken down into multiple stages as illustrated below. It is often an iterative process where a number of optimizations are performed at each step to meet the design performance, area & power requirements.

**Floorplanning :**
	Floorplanning is the first step of physical design. The design is first partitioned into various smaller subsystems based on the system architecture and design requirements. Floorplanning determines the aspect ratio and area of the layout. Here we create the placement rows for standard cells and fix the placement of I/Os around the boundary. Any macros in the design are also placed during the floorplan stage.

Power planning is also typically done during floorplanning. The power grid network is created to distribute power to all the std cells rows, macros and all other components of the design. If there are any special IPs being used in the design then all the IP integration guidelines are also considered in floorplanning.

A good floorplan is very critical to the overall quality of your design.


**Logic Placement :**
	In this stage all the standard cells in the design are placed and assigned a legal location. After the placement EDA tools performs a number of optimizations to improve placement and congestion. A bad placement might lead to larger area utilization and timing issues.

EDA tools also use timing driven placement algorithms to optimize the placement while considering the timing requirements of the design.

**Clock Tree Synthesis :**
	During the Floorplanning & placement stage, the clock is considered as an ideal network. The optimizations in the placement stage are performed based on the assumption of an ideal clock reaching to all flops at the same time. In CTS, a clock network is created to distribute the clock to all flops. This clock tree is built using buffers or inverters along the clock paths of design in order to achieve zero/minimum skew based on design requirement. A good quality clock network is very crucial to meet the timing requirements of the design.

 **Routing :**
 	Once all the standard cells are legally placed and the clock network is synthesized, all the connecting data nets need to be laid out on the metal layers. This is done during the routing stage. After routing all the nets, a number of optimizations are performed based on the design timing requirements and analysis.

**Timing Analysis & Signoff :**
	After the design Routing, static timing analysis is performed on the design. This step is critical to analyze the performance of the design. During STA, we break down the design into timing paths and calculate the signal propagation delay along each path. Then each path is checked for violations of timing constraints. If any path is violated then these violations need to be addressed before signing off on the design.

The timing signoff ensures that all the design elements are meeting the specified timing requirements and the design is working at the desired frequency.

**Physical Verification & Signoff :**
After the routing is completed, the layout must be completely verified to ensure its correct electrical and logical functionality. The physical verification signoff ensures that the design meets all the fabrication specified rules and can be easily manufactured. Various checks that are performed at this stage includes :

    *	DRC (Design Rule Check)
    *	LVS (Layout Vs Schematic)
    *	ERC (Electrical Rule Check)
    *	Antenna check
    *	EM (Electromigration Analysis)

Once the physical verification is done, the layout is streamed out in the form of a GDSII or OASIS file for fabrication which is called design tapeout.
  
The ORFS Directory Structure and File formats:

![Screenshot from 2024-11-26 01-15-07](https://github.com/user-attachments/assets/ef29fbea-3da9-4977-96f6-fc4035aee363)


```
├── OpenROAD-flow-scripts             
│   ├── docker           -> It has Docker based installation, run scripts and all saved here
│   ├── docs             -> Documentation for OpenROAD or its flow scripts.  
│   ├── flow             -> Files related to run RTL to GDS flow  
|   ├── jenkins          -> It contains the regression test designed for each build update
│   ├── tools            -> It contains all the required tools to run RTL to GDS flow
│   ├── etc              -> Has the dependency installer script and other things
│   ├── setup_env.sh     -> Its the source file to source all our OpenROAD rules to run the RTL to GDS flow
```
Now, go to flow directory

![Screenshot from 2024-11-26 01-15-59](https://github.com/user-attachments/assets/3434f9c7-ccc2-42c9-a9ed-34896588bd41)

```
├── flow           
│   ├── design           -> It has built-in examples from RTL to GDS flow across different technology nodes
│   ├── makefile         -> The automated flow runs through makefile setup
│   ├── platform         -> It has different technology note libraries, lef files, GDS etc 
|   ├── tutorials        
│   ├── util            
│   ├── scripts             
```

**4. Automated RTL2GDS for for GCD example:**

In this section, we run the physical design and explore the gui file of gcd design of nangate45 platform. The commands are:-

```
# Assuming you should be inside the OpenROad directory inside flow folder then run below commands.
make # by default makefile will have the gcd as the default design
# or
make DESIGN_CONFIG=./designs/nangate45/gcd/config.mk
make gui_floorplan
make gui_place
make gui_cts
make gui_route
make gui_final
# or we can open the gui file and their we select the .odb file going through the results folder of nangate45 platform
source ./env.sh # go to the OpenROAD directory then run this command then below command
openroad -gui
make metadata
gedit designs/nangate45/gcd/metadata-base-ok.json
```

**Command Screenshot:**

![synth](https://github.com/user-attachments/assets/26e73bf9-750e-4187-b767-84fb0fcfadad)

**Floorplan:**

![floorplan](https://github.com/user-attachments/assets/ae566118-b201-4be3-ad27-09b7f5bbf6e4)

![floorplan_gui1](https://github.com/user-attachments/assets/92695e6d-8224-40fd-b359-761764afa027)


![fplan](https://github.com/user-attachments/assets/22451f5c-5980-4885-bf4f-f49f7aed3ebd)

**Place:**

![place](https://github.com/user-attachments/assets/53ec457b-3073-4341-984d-5fefa509e485)

**CTS:**

![cts](https://github.com/user-attachments/assets/3d1abfeb-404a-4d45-bce3-45165e3af115)

**Route:**

![route](https://github.com/user-attachments/assets/44a494cc-4ef0-4d7e-9770-5e6d96df815a)

**Final GUI:**

![final_gui](https://github.com/user-attachments/assets/7ab4aac4-cb36-4c5d-a3ee-bebb8eb065e2)


## **Using above flow and commands we ran automated RTL2GDS flow for physical design of VSDbabysoc:**

Initial Steps:

*	We need to create a directory vsdbabysoc inside OpenROAD-flow-scripts/flow/designs/sky130hd
*	Now copy the folders gds, include, lef and lib from the VSDBabySoC folder in your system into this directory.
        -	The gds folder would contain the files avsddac.gds and avsdpll.gds
        -	The include folder would contain the files sandpiper.vh, sandpiper_gen.vh, sp_default.vh and sp_verilog.vh
        -	The gds folder would contain the files avsddac.lef and avsdpll.lef
        -	The lib folder would contain the files avsddac.lib and avsdpll.lib
*	Copy the constraints file(vsdbabysoc_synthesis.sdc) from the VSDBabySoC folder in your system into this directory.
*	Copy the files(macro.cfg and pin_order.cfg) from the VSDBabySoC folder in your system into this directory.
*	Create a macro.cfg file whose contents are shown below:

![image](https://github.com/user-attachments/assets/909f4f0f-3079-47bc-8e64-0fa314cb8f95)

![image](https://github.com/user-attachments/assets/d3ba1bf7-9e0a-411e-8d99-cf4f093bb8f4)

Go to terminal and run the following commands:

```
cd OpenROAD-flow-scripts
source env.sh
cd flow
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk 
```

**Step1: Synthesis and Floorplanning:**

	In VLSI design, Floorplanning is a crucial step in physical design that involves placing blocks and macros in the chip or core area.

The primary objectives of floorplanning are to minimize area, timing, wire length, and power consumption while ensuring easy routing and reliability.


**Synthesis reports:**

![Screenshot from 2024-11-26 03-51-02](https://github.com/user-attachments/assets/42cd71d9-519f-4a44-9a08-371aade7be59)
![Screenshot from 2024-11-26 03-50-45](https://github.com/user-attachments/assets/216aaab5-d307-4c81-8d8f-b782ccdf7dff)



**Floorplan Timing reoprt:**

![Screenshot from 2024-11-26 03-51-34](https://github.com/user-attachments/assets/4bc17c40-957d-4a2c-aa3d-5e99003bb1a1)
![Screenshot from 2024-11-26 03-51-25](https://github.com/user-attachments/assets/b20aef16-7541-42c4-b463-9c6bdc706e6c)



**Floorplan openroad GUI output:**


![Screenshot from 2024-11-26 03-40-07](https://github.com/user-attachments/assets/be102aea-7492-4f3e-8394-b004b54220cf)


**Step2: Placement:**

Placement occurs after logic synthesis and before routing in the VLSI design flow. The primary goals of placement include:

*	Timing Optimization: Ensuring that the placement minimizes delays in signal propagation.

*	Power Optimization: Reducing power consumption by minimizing capacitive loads and optimizing wire lengths.

*	Area Optimization: Efficiently utilizing the chip area to avoid congestion and ensure routability.

**Steps in Placement:**

Placement can be divided into several key stages:

*	**Pre-Placement:** This initial stage involves checks and the placement of physical-only cells (e.g., end-cap cells, well-tap cells) to ensure a clean design environment before standard cell placement begins.

*	**Global Placement:** During this phase, the tool determines approximate locations for each standard cell based on various constraints such as timing, congestion, and power. This step does not enforce design rule checks (DRCs), allowing for overlaps.

*	**Legalization:** After global placement, the tool adjusts the positions of cells to eliminate overlaps and ensure that all cells are in legal locations according to the design rules. This process may involve flipping cells to match power pin requirements.

*	**High Fanout Net Synthesis (HFNS):** This step addresses nets with high fanout by distributing the load across multiple drivers and adding buffers as necessary to meet timing constraints[1][2].

*	**Post-Placement Optimization:** After initial placement, further iterations are conducted to refine the design, focusing on timing, congestion, and power optimizations. This may include techniques like scan-chain reordering and tie cell insertion.


In summary, placement is a multi-step process that plays a vital role in the VLSI design flow, impacting timing, power, area optimization, and overall circuit performance.


**Placement Report**

![Screenshot from 2024-11-26 03-53-24](https://github.com/user-attachments/assets/59a5ce09-6b8e-4d29-9709-c67ba2d448fb)
![Screenshot from 2024-11-26 03-53-13](https://github.com/user-attachments/assets/af5bd55f-0ba5-4e5e-917d-186d4d8e530e)
![Screenshot from 2024-11-26 03-53-04](https://github.com/user-attachments/assets/4611efcc-5145-4ff4-821e-e11da6d5e792)


**Screenshots of VSDbabysoc placed macros:**


![Screenshot from 2024-11-26 03-44-17](https://github.com/user-attachments/assets/0bfc21a6-5c80-43f8-99f7-dde103b78fd9)
![Screenshot from 2024-11-26 03-43-58](https://github.com/user-attachments/assets/21a56e2d-2816-4633-952a-4337c99acf31)
![Screenshot from 2024-11-26 03-43-01](https://github.com/user-attachments/assets/4f238777-b4cf-4764-8ea7-766582b8ac2d)


**Step3: Clock Tree Synthesis:**

CTS involves connecting the clock signal from the clock port to the clock pins of sequential cells while minimizing insertion delay and balancing skew. The clock network is typically categorized as a high fanout net, which requires special handling due to its significant power consumption—often accounting for 30-40% of total chip power—and its susceptibility to electromigration (EM) effects.

**Steps in Clock Tree Synthesis:**

The CTS process typically includes the following steps:

*	Preparation: This involves checking the legality of the design, ensuring power connections are correct, and verifying that the timing quality of results (QoR) is acceptable.

*	Clustering: Grouping sink pins based on their geometric locations to facilitate better skew management.

*	Buffer Insertion: Automatically inserting buffers and inverters along the clock paths to manage load and reduce insertion delay.

*	Balancing: Using clock buffers and inverters to achieve a balanced clock distribution across the design.

*	Post-Conditioning: Final adjustments to ensure that all design rules are met and that the clock tree operates within specified parameters for skew and insertion delay.


**Quality Checks Post-CTS:**

After completing the CTS, several checks are necessary to ensure the clock tree meets design goals:

*	Insertion Delay: Must meet target values.
*	Skew Balancing: Should be within acceptable limits.
*	Signal Integrity: Ensuring minimal crosstalk and other noise effects.
*	Power Consumption: Evaluating the clock tree's power usage to ensure it aligns with design specifications.

In summary, Clock Tree Synthesis is a fundamental aspect of VLSI design that directly impacts the performance, power efficiency, and reliability of integrated circuits. Proper execution of CTS ensures that the clock signal is effectively distributed, enabling synchronous operation of all components within the design.


**CTS Reports**

![image](https://github.com/user-attachments/assets/2ee65db1-8810-443e-beaf-97d3709e0a05)
![image](https://github.com/user-attachments/assets/aa199c21-8fac-4b3b-9e20-15ad4c9ea48c)
![image](https://github.com/user-attachments/assets/2d81d0e8-22c4-4e4f-8ae4-1222d79f58bc)


**Heat Map:**

![Screenshot from 2024-11-26 03-31-37](https://github.com/user-attachments/assets/2d2374c4-214b-40ac-b29d-31228a4e2c30)

**Routing Congestion and IO nets:**
![Screenshot from 2024-11-26 03-29-00](https://github.com/user-attachments/assets/bd511e63-05f9-4c20-85c5-e3ebf156511f)


**Step4: Routing:**
-------
There are three main types of routing:

*	Pre-routing (also known as power routing) which is done during power planning.
*	Clock routing performed while building the clock tree in the clock tree synthesis (CTS) stage.
*	Signal routing done after CTS to connect all signal pins.

**Routing Flow**

The routing flow consists of four main stages:

*	Global Routing: Divides the core area into global cells (gcells) and finds the shortest path for each net using algorithms like maze routing and Steiner tree. It assigns nets to specific gcells but does not define actual tracks.

*	Track Assignment: Assigns actual metal layers to global routes while fixing some design rule violations. However, many DRC, signal integrity, and timing violations still remain.

*	Detailed Routing: Completes the actual metal and via connections between pins. It fixes all remaining violations through multiple iterations. The block is divided into switch boxes (Sboxes) for routing.

*	Search and Repair: Performed after the first detailed routing iteration to locate and fix any remaining shorts or spacing violations.

**Routing Constraints:**

Key routing constraints include:

*	Design rule constraints related to manufacturing
*	Performance constraints to meet timing
*	Routing density constraints to avoid congestion
*	Constraints on off-grid routing
*	Blocked routing regions



Screenshot of GUI of routed design:

**Heat map for routing congestion:**

![Screenshot from 2024-11-26 04-32-43](https://github.com/user-attachments/assets/537e08e4-73e8-4fd6-9890-6957a103c326)


**Heat map for placement congestion:**

![Screenshot from 2024-11-26 04-32-16](https://github.com/user-attachments/assets/254a11d1-e3ce-4970-a2a1-2ec972b96c36)


**Routing Report**![Screenshot from 2024-11-26 05-40-48](https://github.com/user-attachments/assets/a875b2ff-c10d-4d12-b54a-add6ea1da697)

![Screenshot from 2024-11-26 05-37-28](https://github.com/user-attachments/assets/dbe11846-5de2-41fb-8af1-7ced3a29cfa9)
![Screenshot from 2024-11-26 05-36-04](https://github.com/user-attachments/assets/40ab242a-9268-4615-a18d-244e9220c1d9)
![Screenshot from 2024-11-26 03-51-02](https://github.com/user-attachments/assets/67b6f4bd-4c1c-4f3f-8360-4ad0b7178d19)


