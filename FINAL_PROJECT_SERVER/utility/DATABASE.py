import mysql.connector
 
def execute_query(query):
    conn= mysql.connector.connect(
        host='localhost',
        port=3306,
        user="root",
        password="StrongPass123!",
        database="sensor_data"
    )
    cursor= conn.cursor()

    cursor.execute(query)

    conn.commit()

    cursor.close()

    conn.close()

def execute_select_query(query):
     conn= mysql.connector.connect(
        host='localhost',
        port=3306,
        user="root",
        password="StrongPass123!",
        database="sensor_data"
    )
     cursor=conn.cursor()
     cursor.execute(query)
     data = cursor.fetchall()
     cursor.close()
     conn.close()
     return data
