## CAN Error frame
 - Single frame with a very high priority which will be sent if a board fails to send a can message (it hasn't been heard from in a while and probably lost arbitration several times) ONLY SEND ONCE -> just to log that there's a problem.

## CAN Tx Buffers / FIFO / Queue
 - CAN protocol prioritizes lower message IDs. If there is a tie between dedicated buffers and the FIFO/queue, the lower message ID, then the lower buffer number is sent first.
 
 - Dedicated Tx Buffers are meant for sending a single CAN message ID per buffer.
  - The buffer is kept after sending, so you only need to modify the data, or simply request to send it again if the data is the same.
 - FIFO buffers are meant for sending messages in the order they're added where the ID and data will change often and you want to specify that older messages should be sent first regardless of the message ID priority.
 - Queue buffers are meant for sending messages in priority order like dedicated buffers, but when more than 32 IDs are being used or you want to queue many messages at a time with the same ID.

Example: I need to send ID 0x305 twice a second with no data.
 - Don't need a fifo or queue since it's going to be a single exact repeated message.
 - Allocate a single dedicated buffer for the message, pre-fill it with 0x305 id with zero data,
  - Then just request it to be sent every 500ms. (You should always check that the previous iteration did in fact send, and have some error logic if it hasn't sent the previous iteration yet).
 - Sleep

Example: I need to send ID 0x300 to 0x32A with varying data, and I want it to send in the order I request it to send.
 - There are more than 32 IDs in use, and you want it to send in the order you request, so that would be a fifo.

Most of the time you'll use dedicated buffers, FIFOs, or a mix of the two (one repeated message with several varying ID messages...)