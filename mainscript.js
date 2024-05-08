const fs = require("fs");
const path = require("path");

// Get the current directory path
const currentDir = __dirname;

// Read the contents of the current directory
fs.readdir(currentDir, (err, files) => {
  if (err) {
    console.error("Error reading directory:", err);
    return;
  }

  // Filter the list to include only directories
  const folders = files.filter((file) => {
    const filePath = path.join(currentDir, file);
    return fs.lstatSync(filePath).isDirectory();
  });

  console.log("Folders in the current directory:", folders);
});
