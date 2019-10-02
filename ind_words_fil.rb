=begin
*************************************************************************************************
*************************************************************************************************
This program distinguish indipendent words from all words.
************************************************************************************************
************************************************************************************************
=end

#Open input file. And make array for words.
inp = File.open(ARGV[0],"r")
M = Array.new

#Substitute indipendent words to matrix M.
puts("m1")
inp.each do |i|
   m1 = i.chomp!.split(",")
   m2 = m1[0].split("\t")

   if (m2[1]=='動詞' || m2[1]=='形容詞' || m2[1]=='名詞' || m2[1]=='副詞' || m2[1]=='接続詞' || m2[1]=='感動詞' || m2[0]=='EOS')
      puts("#{i}\n")
      M.push(i)
   end
end

puts M

#Output matrix M.
outp = File.open(ARGV[1],"w")
puts M
M.each do |i|
#   outp.printf("%s",i)
#   outp.printf("\n")
#   puts i
#   puts("\n")
end

outp.puts(M)

inp.close
outp.close
