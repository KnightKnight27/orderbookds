# Simple Order Book Data Structure

## Messages (Ticks):

- **NEW**: `order_id, price, quantity`
- **MOD**: `order_id, mod_price, mod_quantity`
- **CXL**: `order_id`
- **TRD**: `b_order_id, s_order_id, traded_price, traded_quantity`

Data structure that publishes K (say 5) depth bid, ask `<price, quantity>` tuples every time this data structure has an update.<br>

**Sample Output**
_______________________________
*Bid Depth* <br><br>
Price: 100, Quantity: 55<br> Price: 95, Quantity: 120
_______________________________
*Ask Depth*<br><br>
Price: 100, Quantity: 25<br>
Price: 190, Quantity: 50<br>
_______________________________
