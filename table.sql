DROP TABLE customer CASCADE CONSTRAINTS;
DROP TABLE main_order CASCADE CONSTRAINTS;
DROP TABLE delivery_company CASCADE CONSTRAINTS;
DROP TABLE delivery CASCADE CONSTRAINTS;
DROP TABLE commission CASCADE CONSTRAINTS;
DROP TABLE marketing_team CASCADE CONSTRAINTS;
DROP TABLE order_details CASCADE CONSTRAINTS;
DROP TABLE vendor CASCADE CONSTRAINTS;
DROP TABLE product_type CASCADE CONSTRAINTS;
DROP TABLE product CASCADE CONSTRAINTS;
DROP TABLE purchase_inventory CASCADE CONSTRAINTS;

CREATE TABLE customer (
    CustomerID NUMBER(12,0),
    customer_name VARCHAR(30),
    phone_number NUMBER(10,0),
    Address VARCHAR(40),
    email_address VARCHAR(255),
    customer_type VARCHAR(15),
    CONSTRAINT pk_cust_id PRIMARY KEY(CustomerID)
);

CREATE TABLE main_order (
    OrderID NUMBER(10,0),
    CustomerID NUMBER(12,0),
    date_of_order DATE,
    time_of_order TIMESTAMP,
    CONSTRAINT fk_customer FOREIGN KEY (CustomerID) REFERENCES customer(CustomerID),
    CONSTRAINT pk_order_id PRIMARY KEY(OrderID)
);

CREATE TABLE delivery_company (
    D_CID NUMBER(5),
    name VARCHAR2(30),
    CONSTRAINT pk_d_c PRIMARY KEY(D_CID)
);

CREATE TABLE delivery (
  DeliveryID NUMBER(10, 0),
  OrderID NUMBER(10, 0),
  D_CID NUMBER(10, 0),
  delivery_method VARCHAR2(50),
  delivery_fee NUMBER(10, 2),
  s_date DATE,
  CONSTRAINT fk_order FOREIGN KEY (OrderID) REFERENCES main_order(OrderID),
  CONSTRAINT fk_delivery_company FOREIGN KEY (D_CID) REFERENCES delivery_company(D_CID),
  CONSTRAINT pk_delivery_id PRIMARY KEY(DeliveryID)
);


CREATE TABLE commission (
    OrderID NUMBER(10),
    com_percent DECIMAL(4, 1),
    com_amount NUMBER(6),
    CONSTRAINT fk_order_com FOREIGN KEY (OrderID) REFERENCES main_order(OrderID)
);

CREATE TABLE marketing_team (
    OrderID NUMBER(10),
    market_team_name VARCHAR2(30),
    CONSTRAINT fk_order_mar FOREIGN KEY (OrderID) REFERENCES main_order(OrderID)
);

CREATE TABLE vendor (
    VendorID NUMBER(7),
    business_name VARCHAR2(30),
    cont_per_name VARCHAR2(30),
    cont_num VARCHAR2(11),
    address VARCHAR2(60),
    email_address VARCHAR2(30),
    bank_acc_num VARCHAR2(30),
    CONSTRAINT pk_vendor_id PRIMARY KEY(VendorID)
);

CREATE TABLE product_type (
    P_TypeID NUMBER(7),
    type VARCHAR2(30),
    CONSTRAINT pk_pro_type_id PRIMARY KEY(P_TypeID)
);

CREATE TABLE product (
    ProductID NVARCHAR2(7),
    P_TypeID NUMBER(7),
    pro_name VARCHAR2(60),
    pro_price DECIMAL(5, 2),
    CONSTRAINT fk_pro_type FOREIGN KEY (P_TypeID) REFERENCES product_type(P_TypeID),
    CONSTRAINT pk_pro_id PRIMARY KEY(ProductID)
);

CREATE TABLE order_details (
    OrderID NUMBER(10),
    ProductID NVARCHAR2(7),
    quantity NUMBER(4),
    od_total_price DECIMAL(10, 2),
    CONSTRAINT fk_order_o_d FOREIGN KEY (OrderID) REFERENCES main_order(OrderID),
    CONSTRAINT fk_product FOREIGN KEY (ProductID) REFERENCES product(ProductID)
);

CREATE TABLE purchase_inventory (
    PurchaseID NUMBER(10),
    ProductID NVARCHAR2(7),
    VendorID NUMBER(7),
    date_of_purchase DATE,
    time_of_purchase TIMESTAMP,
    pur_quantity NUMBER(4),
    total_pur_price DECIMAL(10, 2),
    CONSTRAINT fk_product_p_i_id FOREIGN KEY (ProductID) REFERENCES product(ProductID),
    CONSTRAINT fk_vendor FOREIGN KEY (VendorID) REFERENCES vendor(VendorID),
    CONSTRAINT pk_pur_int_id PRIMARY KEY(PurchaseID)
);

INSERT INTO customer VALUES
(1, 'James', '0129237190', '123 Main St', 'james@gmail.com','business');
INSERT INTO customer VALUES
(2, 'Lim', '0127831980', '123 Road St', 'lim@gmail.com', 'personal');
INSERT INTO main_order VALUES
(123, 1, TO_DATE('18/03/2023', 'DD/MM/YYYY'), TO_DATE('10:00', 'HH:MI'));
INSERT INTO main_order VALUES
(124, 2, TO_DATE('29/03/2023', 'DD/MM/YYYY'), TO_DATE('09:00', 'HH:MI'));
INSERT INTO vendor VALUES
(001, 'Sharifah', 'Ali', 0123456789, '7, Jalan Taman Bandar', 'sharifah@gmail.com', 100023234);
INSERT INTO vendor VALUES
(002, 'Bio packaging', 'Abu', 0987456123, '56, Street Town City', 'biopackage@gmail.com', 684984849);
INSERT INTO commission VALUES
(123, 3, 1000);
INSERT INTO commission VALUES
(124, 10, 3000);
INSERT INTO product_type VALUES
(901, 'Sharifah');
INSERT INTO product_type VALUES
(801, 'Bio packaging');
INSERT INTO product VALUES
(2001, 901, 'NASI BRIYANI GAM AYAM', 11.90);
INSERT INTO product VALUES
(2002, 801,'6mm Bio Straw with single wrap (6mm x 210mm)', 320);
INSERT INTO purchase_inventory VALUES
(0011, 2001, 001, TO_DATE('01/02/2023', 'DD/MM/YYYY'), TO_DATE('12:00', 'HH:MI'), 100, 90);
INSERT INTO purchase_inventory VALUES
(0012, 2002, 002, TO_DATE('01/02/2023', 'DD/MM/YYYY'), TO_DATE('12:30', 'HH:MI'), 500, 350);
INSERT INTO order_details VALUES
(123, 2001, 100, 1000);
INSERT INTO order_details VALUES
(124, 2002, 50, 500);
INSERT INTO delivery_company VALUES
(1001, 'Grab');
INSERT INTO delivery_company VALUES
(1002, 'Lalamove');
INSERT INTO delivery VALUES
(4000, 123, 1001,'Motorcycle', 100, TO_DATE('13/04/2023', 'DD/MM/YYYY'));
INSERT INTO delivery VALUES
(4001, 124, 1002, 'Car', 120, TO_DATE('04/09/2023', 'DD/MM/YYYY'));
INSERT INTO marketing_team VALUES
(123, 'RB');
INSERT INTO marketing_team VALUES
(124, 'RC');
