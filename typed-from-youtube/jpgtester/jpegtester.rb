#!/usr/bin/env ruby
def is_jpeg?(file_path)

  # Read 3 bytes
  file = File.open(file_path, "rb")
  bytes = file.read(3)
  bytes.force_encoding("UTF-8")
  file.close

  # Compare
  bytes == "\xFF\xD8\xFF"
end

# Main
if (ARGV.size != 1)
  puts("Usage: jpegtester.rb <file to test>")
  exit(1)
end

fileName = ARGV[0]
if is_jpeg?(fileName)
  puts "Yes"
else
  puts "No"
end
