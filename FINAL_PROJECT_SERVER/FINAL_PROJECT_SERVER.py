from flask import Flask, request, render_template, jsonify
from utility.DATABASE import execute_query, execute_select_query

app = Flask(__name__)

@app.route('/sensors', methods=['POST'])
def insert_multiple_values():
    data = request.get_json()
    location = data.get('location')
    temp = data.get('temperature')
    light = data.get('light')
    gas = data.get('gas')

    query = f"""
        INSERT INTO sensordata (type, location, value)
        VALUES 
            ('temperature', '{location}', {temp}),
            ('LDR', '{location}', {light}),
            ('gas', '{location}', {gas});
    """
    execute_query(query)
    return "All sensor values inserted successfully"

@app.route('/graph-data', methods=['GET'])
def get_graph_data():
    query = "SELECT type, value, timestamp FROM sensordata ORDER BY id DESC LIMIT 25;"
    results = execute_select_query(query)
 
    return jsonify(results)


@app.route('/graph/temperature')
def temperature_graph():
    return render_template('temperature_graph.html')

@app.route('/graph/light')
def light_graph():
    return render_template('light_graph.html')

@app.route('/graph/gas')
def gas_graph():
    return render_template('gas_graph.html')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=4000, debug=True)
