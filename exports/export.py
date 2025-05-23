# Disclaimer: written by ChatGPT. (Although, you probably already knew that.)
# This tool converts test case files generated by Codeforces into the Hackerrank format.

import os
import shutil
import zipfile

def list_contest_folders(base_dir):
    return [folder for folder in os.listdir(base_dir) 
            if os.path.isdir(os.path.join(base_dir, folder)) 
            and folder.startswith("contest") 
            and not folder.endswith("_tests")]


def process_directory(base_dir, output_parent):
    print(base_dir)
    for root, dirs, files in os.walk(base_dir):
        # Skip processing the output parent directory itself if found in traversal
        if output_parent in root:
            continue
        
        # Check if all files match the expected format
        valid_files = True
        for file in files:
            base_name = file.split('.')[0]
            ext = file.split('.')[1] if '.' in file else ''
            if not (base_name.isdigit() or (base_name.isdigit() and ext == 'a')):
                valid_files = False
                break
        
        if valid_files and files:
            relative_path = os.path.relpath(root, base_dir)
            output_folder_path = os.path.join(output_parent, relative_path)
            input_folder_path = os.path.join(output_folder_path, "input")
            output_folder_subpath = os.path.join(output_folder_path, "output")
            export_folder_path = os.path.join(output_parent, "export")
            
            os.makedirs(input_folder_path, exist_ok=True)
            os.makedirs(output_folder_subpath, exist_ok=True)
            os.makedirs(export_folder_path, exist_ok=True)
            
            for file in files:
                file_path = os.path.join(root, file)
                base_name = file.split('.')[0]  # Extracts the numeric part
                ext = file.split('.')[1] if '.' in file else ''
                
                try:
                    index = int(base_name) - 1  # Convert to zero-based index
                    if ext == 'a':
                        target_path = os.path.join(output_folder_subpath, f"output{index:02}.txt")
                    else:
                        target_path = os.path.join(input_folder_path, f"input{index:02}.txt")
                    
                    shutil.copy(file_path, target_path)
                except ValueError:
                    pass  # Skip files that don't match expected format
    
    # Create zipped archives for each processed folder that follows problems/problem_name/tests structure
    for root, dirs, _ in os.walk(output_parent):
        if root.endswith("tests") and "input" in dirs and "output" in dirs:
            problem_name = os.path.basename(os.path.dirname(root))
            export_folder_path = os.path.join(output_parent, "export")
            os.makedirs(export_folder_path, exist_ok=True)
            zip_filename = os.path.join(export_folder_path, f"{problem_name}.zip")
            
            with zipfile.ZipFile(zip_filename, 'w', zipfile.ZIP_DEFLATED) as zipf:
                for folder_root, _, files in os.walk(root):
                    for file in files:
                        file_path = os.path.join(folder_root, file)
                        arcname = os.path.relpath(file_path, root)
                        zipf.write(file_path, arcname)



if __name__ == "__main__":
    base_directory = os.getcwd()  # Use current working directory
    contest_folders = list_contest_folders(base_directory)
    
    if not contest_folders:
        print("No contest folders found.")
    else:
        print("Available contest folders:")
        for folder in contest_folders:
            print(f"- {folder}")
        
        contest_id = input("Enter contest ID: ")
        contest_directory = f"contest-{contest_id}"
        if contest_directory in contest_folders:
            output_parent_directory = os.path.join(base_directory, contest_directory + "_tests")
            os.makedirs(output_parent_directory, exist_ok=True)
            process_directory(os.path.join(base_directory, contest_directory), output_parent_directory)
        else:
            print("Invalid contest folder name.")
