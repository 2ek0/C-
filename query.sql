DROP VIEW delivery_detail;

CREATE VIEW delivery_detail AS
SELECT o.OrderID, d.DeliveryID, dc.Name
FROM main_order o
INNER JOIN delivery d ON o.OrderID = d.OrderID
INNER JOIN delivery_company dc ON d.D_CID = dc.D_CID
WHERE d.OrderID IS NOT NULL;

DROP VIEW droder;

CREATE VIEW dorder AS
SELECT customer_name, pro_name
FROM customer c, main_order mn, order_details od, product p
WHERE c.customerid = mn.customerid and mn.orderid = od.orderid and p.productid = od./productid;

DROP VIEW commission_view;

CREATE VIEW commission_view AS
SELECT o.orderid,com_percent, com_amount, market_team_name 
FROM main_order o, commission c, marketing_team m 
WHERE o.orderid = c.orderid and o.orderid = m.orderid; 

DROP VIEW TotalProfitView;

CREATE VIEW TotalProfitView AS
SELECT SUM(order_revenue) - SUM(comission_amount) - SUM(purchase_expense) AS total_profit
FROM (
    SELECT 
        SUM(od.quantity * p.pro_price) AS order_revenue,
        SUM(c.com_amount) AS comission_amount,
        SUM(pi.pur_quantity * pi.total_pur_price) AS purchase_expense
    FROM 
        main_order o
        JOIN order_details od ON o.orderId = od.OrderId
        JOIN Product p ON od.productid = p.productid
        LEFT JOIN Commission c ON o.OrderId = c.OrderId
        LEFT JOIN purchase_inventory pi ON od.productid = pi.productid
    GROUP BY 
        o.OrderId
) subquery;

DROP VIEW stock;

CREATE VIEW stock AS
SELECT pi.ProductID, p.pro_name, SUM(pi.pur_quantity) AS total_stock
FROM purchase_inventory pi
INNER JOIN product p ON pi.ProductID = p.ProductID
GROUP BY pi.ProductID, p.pro_name;


SELECT product.ProductID, product.pro_name, SUM(order_details.quantity) as total_order_quantity
FROM product
JOIN order_details ON product.ProductID = order_details.ProductID
JOIN main_order ON order_details.OrderID = main_order.OrderID
JOIN purchase_inventory ON product.ProductID = purchase_inventory.ProductID
JOIN vendor ON purchase_inventory.VendorID = vendor.VendorID
WHERE vendor.business_name = 'Sharifah'
GROUP BY product.ProductID, product.pro_name
ORDER BY total_order_quantity DESC;





