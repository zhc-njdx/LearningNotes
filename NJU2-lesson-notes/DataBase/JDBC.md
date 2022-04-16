### JDBC

> 参考[w3cschool教程](https://www.w3cschool.cn/jdbc)

> Java DateBase Connectivity
>
> 用于连接 Java程序 和 数据库 的 API

#### 1 配置

1.1 安装Java JDK 环境 + MySQL

1.2 导入 mysql-connector-java-8.0.28.jar

1.3 连接数据库

```java
Class.forName(JDBC_DRIVER); // 注册数据库
Connection conn = DriverManager.getConnection(DB_URL, USER, PASS); // 连接数据库
```

#### 2 Statement 对象

##### 2.1 Statement

```java
Statement stmt = null;
try{
    stmt = conn.creatStatement();
    String SQL = "select * from employees";
    // ResultSet executeQuery(String SQL);
    ResultSet rs = stmt.executeQuery(SQL);
}
catch (SQLExecption e){
    //...
}
finally{
    stmt.close();
}
```

##### 2.2 PreparedStatement

```java
try{
    // 参数用 ? 代替
    String SQL = "update employees set age = ? where id = ?";
    pstms = conn.prepareStatement(SQL);
    // 使用 void setXXX(int parameterIndex,XXX value);
    // XXX 是参数类型，即SQL语句中 ? 对应字段在数据库中的类型 (age 是 int, id 是 int)
    pstms.setInt(1,20);
    pstms.setInt(2,100);
    // int executeUpdate(String SQL); 
    // 但是这里不用加 SQL; 否则会报错
    pstms.executeUpdate();
}
catch (SQLException e){
    //...
}
finally {
    pstmt.close();
}
```

##### 2.3 CallableStatement

> 暂不学习

##### 2.4 区别

| 接口              | 特点                              |
| ----------------- | --------------------------------- |
| Statement         | 适合执行静态SQL语句，不接受参数   |
| PreparedStatement | 适合执行动态SQL语句，可以接受参数 |
| CallableStatement | 适用于数据库存储过程              |

#### 3 结果集 ResultSet

##### 3.1 移动

```java
public boolean next() throws SQLExpection; // 将光标移到下一行，超出范围返回false
public boolean previous() throws SQLExpection; // 将光标移到上一行，超出范围返回false
```

##### 3.2 查看

```java
public Type getType(String columnName) throws SQLException; // 返回该行{此列名下}的数据
public Type getType(int columnIndex) throws SQLException; // 返回该行{此下标对应列}的数据
```

#### 4 使用模板

```java
import java.sql.*;
import java.math.*;

public class main {
    // JDBC driver name and database URL
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    // 'jdbc:mysql://{hostname}/{databasename}'
    static final String DB_URL = "jdbc:mysql://localhost/EMP"; 

    //  Database credentials
    static final String USER = "root";
    static final String PASS = "123456";

    public static void main(String[] args) {
        Connection conn = null;
        Statement stmt = null;
        PreparedStatement pstmt = null;
        
        try {
            //STEP 2: Register JDBC driver
            Class.forName(JDBC_DRIVER);

            //STEP 3: Open a connection
            System.out.println("Connecting to database...");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            
			/*
			* manipulate database
			**/
            
            if(stmt != null) stmt.close();
            if(pstmt != null) pstmt.close();
            if(conn != null) conn.close();
            
        } catch (SQLException se) {
            //Handle errors for JDBC
            se.printStackTrace();
        } catch (Exception e) {
            //Handle errors for Class.forName
            e.printStackTrace();
        } finally {
            //finally block used to close resources
            try {
                if (stmt != null)
                    stmt.close();
                if(pstmt != null)
                    pstmt.close();
            } catch (SQLException se2) {}// nothing we can do
            try {
                if (conn != null)
                    conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }//end finally try
        }//end try
        System.out.println("END!");
    }
}
```



