# Memory Design
The project spec requires that we emulate a memory system like the one that is
happening at a low level using our "high-level" language. This entails having a
method of addressing memory via binary addresses, as well as separating the
memory space into three primary sectors:

- Text (code)
- Data (constants and variables)
- Stack

The project spec separates this into five pieces, where text and data each have
both a user and a kernel sector. We decided against this model because we
shouldn't be doing anything with the kernel sectors.

## Sections of Memory
Our memory module should be comprised of three subspaces, each identifying a
different, relevant piece of information: text (which is the code we read in),
data (which is the associated data like constants and variables), and stack
(which is a section that will only be accessed by the stack-based simulator,
  but should certainly exist anyways).

### Text

### Data

### Stack

## Representation of Memory Sections
