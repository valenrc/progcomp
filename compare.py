# credits: giyu51/file-difference-checker
# license: MIT
# Use: python3 compare.py --file1 <file1> --file2 <file2> 
import argparse
import re
import difflib
import sys
class bcolors:
    HEADER = '\033[95m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    #UNDERLINE = '\033[4m'

# Dictionary to map ANSI codes to HTML
ansi_to_html = {
    '\033[95m': '<span style="color: #ff00ff">',
    '\033[92m': '<span style="color: #00ff00">',
    '\033[93m': '<span style="color: #ffff00">',
    '\033[91m': '<span style="color: #ff0000">',
    '\033[0m': '</span>',
    '\033[1m': '<strong>',
    '\033[4m': '<u>'
}

def line_difference(line1: str, line2: str) -> tuple[str, str]:
    """
    Prints the difference between two lines character by character.
    Different characters are highlighted in red.
    """
    # Calculate maximum length to handle lines of different lengths
    max_length = max(len(line1), len(line2))
    
    # Create output strings
    output1 = ""
    output2 = ""
    
    # Compare character by character
    for i in range(max_length):
        # Get characters at position i (or empty if beyond length)
        char1 = line1[i] if i < len(line1) else " "
        char2 = line2[i] if i < len(line2) else " "
        
        # If characters are different, add color formatting
        if char1 != char2:
            output1 += f"{bcolors.FAIL}{char1}{bcolors.ENDC}"
            output2 += f"{bcolors.FAIL}{char2}{bcolors.ENDC}"
        else:
            output1 += char1
            output2 += char2
    
    # Print the two lines
    return (output2, output1)

def ansi_to_html_convert(text: str) -> str:
    """
    Converts ANSI codes in the text to HTML format.
    """
    for ansi_code, html_tag in ansi_to_html.items():
        text = text.replace(ansi_code, html_tag)
    return text

def generate_html_report(buffer: list[str], file1: str, file2: str) -> str:
    """
    Generates an HTML report from the output buffer.
    """
    html_content = f"""<!DOCTYPE html>
    <html>
    <head>
        <title>Output Diff</title>
        <style>
            body {{ font-family: monospace; }}
            pre {{ white-space: pre-wrap; }}
        </style>
    </head>
    <body>
        <h1>Output Diff</h1>
    <pre>"""
    
    for line in buffer:
        html_content += ansi_to_html_convert(line) + "\n"
    html_content += """</pre>
    </body>
    </html>"""
    return html_content

allowLogs = False       # Set this variable to True or False as needed
maxTerminalLogs = 10    # Set the maximum number of logs to display

# Exceptions: Specify the keywords that the statements in your code start with.
# For example, if a statement in your code is "server_id = 103", you can specify "server_id" as an exception.
exceptions = []

# Display additional info about data processing
def log_print(*args):
    if allowLogs:
        print("------", *args, '\n')


# Remove newline characters from the line
def filterLine(line: str):
    filteredLine = re.sub(r"(\n|\\n|\r)+", "", line)
    return filteredLine.strip()


# Filter out empty strings from the list
def filterList(lst: list):
    filteredList = [line for line in lst if line != ""]
    return filteredList


# Checks whether line starts with exception keyword
def isLineHaveException(line: str):
    if exceptions:
        for excp in exceptions:
            if line.startswith(excp):
                return True
    return False


# Compare the contents of two files
def differ(file1, file2):
    output_buffer = []

    global exceptions

    print(f"\nComparing {file1} and {file2}")

    if file_exceptions:
        exceptions = [excp.strip('[').strip(',').strip(']')
                      for excp in file_exceptions]
        log_print(f"Exceptions: {exceptions}")
    else:
        log_print('There are no exceptions')

    try:
        # Attempt to open the files
        with open(file1_path, 'r') as firstFile, open(file2_path, 'r') as secondFile:
            # Read the lines from the files
            raw_file1_lines = firstFile.readlines()
            raw_file2_lines = secondFile.readlines()

    except FileNotFoundError as e:
        log_print(f"Error: {e}")
        sys.exit(1)  # Terminate the script with a non-zero exit code

    # Check if the files are identical
    print(f"Lines of {file1}: {len(raw_file1_lines)}")
    print(f"Lines of {file2}: {len(raw_file2_lines)}\n")

    if raw_file1_lines == raw_file2_lines:
        return f"{bcolors.OKGREEN}✓ No differences found{bcolors.ENDC}\n"

    # Filter the lines in each file
    filtered_file1_lines = [filterLine(line) for line in raw_file1_lines]
    filtered_file2_lines = [filterLine(line) for line in raw_file2_lines]

    # Filter out empty lines
    filtered_file1_lines = filterList(filtered_file1_lines)
    filtered_file2_lines = filterList(filtered_file2_lines)

    # Check if the filtered files are identical
    if filtered_file1_lines == filtered_file2_lines:
        return "f{bcolors.OKGREEN}✓ No differences found{bcolors.ENDC}\n"

    # Find the differences between the files
    maxLines = max(len(filtered_file1_lines), len(filtered_file2_lines))
    lineCounter = 0
    totalDifferences = 0

    while lineCounter < maxLines:
        try:
            file1_line = filtered_file1_lines[lineCounter]
            file2_line = filtered_file2_lines[lineCounter]

            if file1_line != file2_line:
                # Check for exceptions
                if isLineHaveException(file1_line) and isLineHaveException(file2_line):
                    log_print('EXCEPTION:', file1_line, '\n', file2_line)
                else:
                    diff_line1, diff_line2 = line_difference(file1_line, file2_line)
                    
                    # Format the output message
                    message = f'{totalDifferences+1} - Line {lineCounter+1}:\n File {file1}: In < {diff_line1} > \n File {file2}: In < {diff_line2} >\n'

                    if totalDifferences < maxTerminalLogs:
                        print(message)
                    elif totalDifferences == maxTerminalLogs:
                        print(f"---Total {totalDifferences}+ differences written into ouputdiff.html---")
                    
                    # Add to output buffer
                    output_buffer.append(message)
                    totalDifferences += 1

        except IndexError:
            # If the line numbers are not equal
            moreLineFile = filtered_file1_lines if len(
                filtered_file1_lines) == maxLines else filtered_file2_lines

            larger_file = file1 if moreLineFile == filtered_file1_lines else file2
            print(
                f'Only file {larger_file} has: < {moreLineFile[lineCounter]} >')
            totalDifferences += 1

        lineCounter += 1

    print(f"{bcolors.FAIL}✖{bcolors.ENDC} Total Differences Found: {bcolors.BOLD}{totalDifferences}{bcolors.ENDC}")
    output_buffer.append(f"{bcolors.FAIL}X{bcolors.ENDC} Total differences found: {bcolors.BOLD}{totalDifferences}{bcolors.ENDC}\n")

    # Generate HTML report
    # Writes the report in the same directory in the outputdiff.html file
    try:
        with open("outputdiff.html", "w") as html_file:
            html_content = generate_html_report(output_buffer, file1, file2)
            html_file.write(html_content)
    except Exception as e:
        print(f"Error writing to HTML file: {e}")

    # Return difference percentage
    matcher = difflib.SequenceMatcher(
        None, filtered_file1_lines, filtered_file2_lines)
    fileSimilarity = round(matcher.ratio() * 100, 2)
    return f"Files equal: {bcolors.HEADER}{fileSimilarity}%{bcolors.ENDC}"


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Compare two files.")
    parser.add_argument(
        "--file1", help="Path to the first file", required=True)
    parser.add_argument(
        "--file2", help="Path to the second file", required=True)
    parser.add_argument(
        "--exceptions",
        nargs="*",
        help=("Exception lines that are not counted")
    )
    args = parser.parse_args()

    file1_path = args.file1
    file2_path = args.file2
    file_exceptions = args.exceptions

    try:
        print(differ(file1_path, file2_path))
    except Exception as e:
        print(f"An error occurred: {e}")