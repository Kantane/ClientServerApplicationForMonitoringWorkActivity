from flask import Flask, request

app = Flask(__name__)

@app.route('/log', methods=['POST'])
def log_activity():
    data = request.get_data(as_text=True)
    print("Received Data:\n", data)
    return "Data logged successfully", 200

if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5000)