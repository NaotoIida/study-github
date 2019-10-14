=begin 
************************************************************************************************
************************************************************************************************
This program is my first ruby program. For this reason, I maynot completery write it.
This program is to culcurate average and variance of words in text.
Needed arguments are inputfilename, outputfilename, and number of words in text.
************************************************************************************************
************************************************************************************************
=end

#Open input file. And make array for word and vector.
inp = File.open(ARGV[0],"r")
M = Array.new

#Substitute data to matrix M.
inp.each do |i|
   M.push(i.chomp!.split(","))
end
#Convert from char to munber.
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

#Step1, Calculate C(r,s).
 sum_w = Array.new(201,0)
 wi = Array.new(201,0)
 c_list = Array.new
 r = 1 #Pramater starting sentence
 s = 1 #Pramater ending sentence
 s_max = 2 #Pramater preventing to reverce
 rm_i = 0 #parameter considered about extra i
 
 while r != (s_max )
       M.each_with_index do |outer_array,i|
	  if r <= s 
             200.times do |k|
             sum_w[k+1] += M[i][k+1]
             end
             if M[i][0] == 'EOS'
		200.times do |k|
                wi[k+1] = sum_w[k+1] / ((i + 1) - rm_i)
                end
                c_label = 0
                ((i + 1) - rm_i).times do |j|
                   200.times do |k|
                   c_label += ((M[rm_i+j][k+1] - wi[k+1]) ** 2) #If use push method, C will be more compact.
                   end
                end
		c_list.push(c_label)
                s += 1
             end
	  
	  elsif M[i][0] =="EOS"
	     s += 1
	     rm_i = i + 1
	  end
          
	  if s_max < s
	     s_max = s
	  end

       end

       r += 1
       200.times do |k|
       sum_w[k+1] = 0
       end
       s = 1

 end

 c_list.each do |k|
    p k
 end
#Put out C() to output file.
 outp = File.open(ARGV[1],"w")
 c_list.each do |i|
    outp.printf("%f,",i)
 end

#Step2
 s_max = s_max-1  #reset s_max to exact number.
 c_array = Array.new(s_max).map{Array.new(s_max,1000)}
 k = 0
 
 1.upto(s_max) do |i|
    1.upto(s_max) do|j|
       if i <= j
          c_array[i-1][j-1] = c_list[k]
	  k += 1
       end
    end
 end

 p "c_array"
 c_array.each do |outer|
    p outer
 end

#Saerch arg_minC().
 e_min = Array.new(s_max).map{Array.new(s_max).map{Array.new(2,1000)}}
 
 for h in 2..s_max
	 for t in 2..h
	    if e_min[h-1][1][1] > c_array[0][t-2]+c_array[t-1][h-1]
			 e_min[h-1][1][0] = t
			 e_min[h-1][1][1] = c_array[0][t-2]+c_array[t-1][h-1]
            end
	 end
 end

 p "e_min" 
 e_min.each do |i|
    p i
 end

#Step3, Saerch arg_mine().
#Saerch arg_mine().
 
 3.upto(s_max) do |q|
    q.upto(s_max) do |h|
       q.upto(h) do |t|
	  if e_min[t-1][q-1][1] > e_min[t-2][q-2][1]+c_array[t-1][h-1]
	     e_min[t-1][q-1][0] = t
             e_min[t-1][q-1][1] = e_min[t-2][q-2][1]+c_array[t-1][h-1]
	  end
       end
    end
 end

 p "e_min" 
 e_min.each do |i|
    p i
 end

#Step4, separate segments.
 p "Please input number."
 j = $stdin.gets.to_i
 g = s_max
 res = Array.new

 j.downto(2) do |i|
    res.push(e_min[g-1][i-1][0])
    g = e_min[g-1][i-1][0]
 end
 
 p res

inp.close
outp.close
