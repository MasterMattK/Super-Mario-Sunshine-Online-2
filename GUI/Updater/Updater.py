import requests
import zipfile
import os
import shutil
import filecmp
import sys
import threading
from PySide6.QtWidgets import QWidget, QProgressBar, QLabel, QMessageBox, QApplication
from PySide6.QtCore import QCoreApplication

class Updater(QWidget):
    def __init__(self, reject=False):
        super().__init__()
        self.setWindowTitle("Super Mario Sunshine Online Updater")
        self.setGeometry(100, 100, 500, 200)

        self.progress_bar = QProgressBar(self)
        self.progress_bar.setGeometry(20, 60, 460, 20)
        self.progress_label = QLabel(self)
        self.progress_label.setGeometry(20, 90, 460, 20)

        if reject:
            QMessageBox.critical(self, "Updater Error", "This updater is only meant to be called from the SMSO executable. Don't run it directly.")
            sys.exit()
        else:
            self.update()

    def update(self):
        self.update_thread = threading.Thread(target=self.update_process)
        self.update_thread.start()

    def update_process(self):
        self.set_progress_label("Downloading update...", 0)
        current_directory = os.path.abspath(os.path.dirname(sys.argv[0]))
        zip_file_path = os.path.join(current_directory, 'updated.zip')
        
        """response = requests.get(f'https://api.github.com/repos/MasterMattK/Super-Mario-Sunshine-Online-2/releases/latest')
        print(response)
        assets = response.json()['assets']
        download_url = assets[0]['browser_download_url']
        full_size = int(assets[0]['size'])
        current_size = 0


        with requests.get(download_url, stream=True) as r:
            r.raise_for_status()
            with open(zip_file_path, 'wb') as f:
                for chunk in r.iter_content(chunk_size=8192):
                    f.write(chunk)
                    current_size += 8192
                    self.set_progress_label("Downloading update...", int((current_size/full_size)*100))"""

        # extract updated files into temp folder
        self.set_progress_label("Extracting files...", 0)
        with zipfile.ZipFile(zip_file_path, 'r') as zip_ref:
            temp_dir = os.path.join(current_directory, 'temp')
            zip_ref.extractall(temp_dir)
            

        self.set_progress_label("Updating files...", 0)
        files_to_skip = ['config.ini', 'Model Data']

        for root, dirs, files in os.walk(os.path.join(temp_dir, 'updated')):
            for file in files:
                file_path = os.path.join(root, file)
                relative_path = os.path.relpath(file_path, temp_dir)
                current_file_path = os.path.join(current_directory, relative_path)
                print(file_path == current_file_path)
                """if os.path.exists(current_file_path):
                    # Compare the contents of the file in the temporary directory to the corresponding file in the current directory
                    if filecmp.cmp(file_path, current_file_path):
                        # The files are the same, so skip this file
                        continue

                # we don't want to override some files
                if [fskip in file_path for fskip in files_to_skip]:
                    continue

                new_file_path = os.path.join(current_directory, relative_path)
                os.makedirs(os.path.dirname(new_file_path), exist_ok=True)
                shutil.copyfile(file_path, new_file_path)"""

        shutil.rmtree(temp_dir)
        #os.remove(zip_file_path)

        self.set_progress_label("Update complete.", 100)
        QMessageBox.information(self, "Updater", "The update is complete.")

    def set_progress_label(self, text, bar_value):
        # Update the progress label text
        self.progress_label.setText(text)
        self.progress_bar.setValue(bar_value)

if __name__ == "__main__":
    reject = False
    # we want to verify that this updater is being called by the SMSO executable
    if len(sys.argv) <= 1 or sys.argv[1] != 'smso-update':
        print("This updater is only meant to be called from the SMSO executable. Don't run it directly.")
        reject = True

    app = QApplication([])
    updater = Updater(reject=reject)
    updater.show()
    app.exec()