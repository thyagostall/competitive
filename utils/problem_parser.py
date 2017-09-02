def create_table_problems(conn):
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

def create_table_references(conn):
    sql = """
        CREATE TABLE IF NOT EXISTS problem_references (
            chapter TEXT NOT NULL, 
            subchapter TEXT NOT NULL, 
            category TEXT NOT NULL, 
            problem_id INTEGER NOT NULL PRIMARY KEY, 
            starred INTEGER NOT NULL, 
            
            FOREIGN KEY(problem_id) REFERENCES problems(id)
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

def download_problem_references():
    import urllib.request
    import json

    with urllib.request.urlopen('http://uhunt.onlinejudge.org/api/cpbook/3') as response:
        raw = response.read()

    raw = json.loads(raw)
    problems = [(chapter['title'], subchapter['title'], problems[0], problem) for chapter in raw for subchapter in chapter['arr'] for problems in subchapter['arr'] for problem in problems[1:]]
    return [tuple([ref[0], ref[1], ref[2], abs(ref[3]), ref[3] < 0]) for ref in problems]

def make_param_marks(qty):
    parameters = ['?'] * qty
    return ', '.join(parameters)

def save_problems(problems, references):
    import sqlite3
    try:
        conn = sqlite3.connect('problems.db')
    
        create_table_problems(conn)
        create_table_references(conn)
        
        c = conn.cursor()
        
        c.executemany("INSERT OR IGNORE INTO problems VALUES (" + make_param_marks(21) + ")", problems)
        c.executemany("INSERT OR IGNORE INTO problem_references VALUES (" + make_param_marks(5) + ")", references)
        conn.commit()
    finally:
        conn.close()

if __name__ == '__main__':
    print("Downloading problems...")
    problems = download_problems()
    
    print("Downloading references...")
    references = download_problem_references()

    print("Saving...")
    save_problems(problems, references)

    print("OK")
