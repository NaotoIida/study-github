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

#Calculate ave_w. ave_w means average of whole of text.
ave_w = Array.new(201,0)

j = 0
M.each do |outer_array|
   200.times do |i|
         ave_w[i+1] += (M[j][i+1])
   end
   j += 1
end

200.times do |i|
   ave_w[i+1] /= M.length
end

#Calculate A. A means variance of whole of text.
 A = Array.new(201,0)
 j = 0
 M.each do |outer_array|
    i = 0
    200.times do |i|
	  A[i+1] += ((M[j][i+1] - ave_w[i+1]).abs ** 2)
    end 
    j += 1
 end
 p A

#Put out calculate data to output file.
 outp = File.open("data/cal_breadcrumb.txt","w")
 ave_w.each do |i|
    outp.printf("%f,",i)
 end
 outp.putc("\n")
 A.each do |i|
    outp.printf("%f,",i)
 end
 outp.putc("\n") 

#Calculate C(r,s).
 sum_w = Array.new(201,0)
 wi = Array.new(201,0)
 C = Array.new(M.length/3).map{Array.new(M.length/3).map{Array.new(201,0)}}
 r = 1 #Pramater starting sentence
 s = 1 #Pramater ending sentence
 s_max = 1 #Pramater preventing to reverce
 rm_i = 0 #parameter considered about extra i
 
 while r != (s_max + 1)
       M.each_with_index do |outer_array,i|
	  if r <= s 
             200.times do |k|
                sum_w[k+1] += M[i][k+1]
             end
             if M[i][0] == 'EOS'
                200.times do |k|
                   wi[k+1] = sum_w[k+1] / ((i + 1) - rm_i)
                end
                ((i + 1) - rm_i).times do |j|
                   200.times do |k|
                      C[r][s][k+1] += ((M[j][k+1] - wi[k+1]).abs ** 2) #If use push method, C will be more compact.
                   end
		   C[r][s][0] = r
                end
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
	  wi[k+1] = 0
       end
       s = 1
 end

#Put out C() to output file.
 C.each do |outer_array|
    outer_array.each do |midle_array|
       midle_array.each do |inner_array|
          outp.printf("%f,",inner_array)
       end
       outp.putc("\n")
    end
 end

#Mark parts of "EOS" in the text to end_s.
 end_s =Array.new
 M.each_with_index do |data,i|
    if M[i][0] == "EOS"
	    end_s.push(i)
    end
 end

#Saerch arg_minC().
 mincost = Array.new(end_s.length).map{Array.new(2,1000)}
 cost1 = 0
 cost2 = 0
 
 for h in 2..end_s.length
	 for t in 2..h
		 200.times do |i|
		    cost1 += C[1][t-1][i+1]**2
		    cost2 += C[t][h][i+1]**2
		 end
		 cost1 = Math.sqrt(cost1)
		 cost2 = Math.sqrt(cost2)
		 if mincost[h-1][1] > cost1+cost2
			 mincost[h-1][0] = t
			 mincost[h-1][1] = cost1+cost2
		 end
	 end
 end

#Put out arg_minC() to output file.
 mincost.each_with_index do |outer_array,i|
    outp.printf("%d,",mincost[i][0])
    outp.printf("%f,",mincost[i][1])
    outp.putc("\n")
 end
 
 inp.close
outp.close