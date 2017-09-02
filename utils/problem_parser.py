def create_table(conn):
    sql = """
        CREATE TABLE IF NOT EXISTS problems (
        id INTEGER NOT NULL PRIMARY KEY,
        number INTEGER NOT NULL,
        title INTEGER NOT NULL,
        dacu INTEGER NOT NULL,
        best_runtime_of_an_accepted_submission INTEGER NOT NULL,
        best_memory_used_of_an_accepted_submission INTEGER NOT NULL,
        no_verdict_given INTEGER NOT NULL,
        submission_error INTEGER NOT NULL,
        cant_be_judged INTEGER NOT NULL,
        in_queue INTEGER NOT NULL,
        compilation_error INTEGER NOT NULL,
        restricted_function INTEGER NOT NULL,
        runtime_error INTEGER NOT NULL,
        output_limit_exceeded INTEGER NOT NULL,
        time_limit_exceeded INTEGER NOT NULL,
        memory_limit_exceeded INTEGER NOT NULL,
        wrong_answer INTEGER NOT NULL,
        presentation_error INTEGER NOT NULL,
        accepted INTEGER NOT NULL,
        run_time_limit INTEGER NOT NULL,
        status INTEGER NOT NULL
    );
    """
    conn.execute(sql)
    

def download_problems():
    import urllib.request
    import json

    with urllib.request.urlopen('http://uhunt.onlinejudge.org/api/p') as response:
        raw = response.read()

    problems = json.loads(raw)
    return [tuple(problem[:21]) for problem in problems]

def save_problems(problems):
    import sqlite3
    try:
        conn = sqlite3.connect('problems.db')
    
        create_table(conn)
        
        c = conn.cursor()
        parameters = ['?'] * 21
        parameters = ', '.join(parameters)
        
        c.executemany("INSERT OR IGNORE INTO problems VALUES (" + parameters + ")", problems)
        conn.commit()
    finally:
        conn.close()

print("Downloading problems...")
problems = download_problems()

print("Saving...")
save_problems(problems)

print("OK")
