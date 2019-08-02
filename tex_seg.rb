=begin 
************************************************************************************************
************************************************************************************************
This program is my first ruby program. For this reason, I maynot completery write it.
This program is to culcurate average and variance of words in text.
Needed arguments are inputfilename, outputfilename, and number of words in text.
************************************************************************************************
************************************************************************************************
=end

inp = File.open(ARGV[0],"r")

M = Array.new

inp.each do |i|
   M.push(i.chomp!.split(","))
end

j = 0
M.each do |outer_array|
   i = 0
   outer_array.each do |inner_array|
      if i != 0 then
         M[j][i] = inner_array.to_f
      end
      i += 1
   end
   j += 1
end

ave_w = Array.new(201,0)

j = 0
M.each do |outer_array|
   200.times do |i|
         ave_w[i+1] += (M[j][i+1] * 100)
   end
   j += 1
end

ave_w.each do |i|
   ave_w[i] /= M.length
   p ave_w[i]
end

inp.close
