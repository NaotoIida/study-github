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

#Put out calculate data to output file.
 outp = File.open(ARGV[1],"w")
 ave_w.each do |i|
    outp.printf("%f,",i)
 end
 outp.putc("\n")
 A.each do |i|
    outp.printf("%f,",i)
 end
 outp.putc("\n") 

#Step1, Calculate C(r,s).
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
                      C[r][s][k+1] += ((M[rm_i+j][k+1] - wi[k+1]).abs ** 2) #If use push method, C will be more compact.
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

#Step2, Mark parts of "EOS" in the text to end_s.
 end_s =Array.new
 M.each_with_index do |data,i|
    if M[i][0] == "EOS"
	    end_s.push(i)
    end
 end

 p ("end_s")
 end_s.each do |i|
    p i
 end

#Saerch arg_minC().
 mincost = Array.new(end_s.length).map{Array.new(2,1000)}
 cost1 = 0
 cost2 = 0
 c_nol = Array.new #This array for keep nolm all C() for step3.
 
 for h in 2..end_s.length
	 for t in 2..h
		 200.times do |i|
		    cost1 += C[1][t-1][i+1]**2
		    cost2 += C[t][h][i+1]**2
		 end
		 cost1 = Math.sqrt(cost1)
		 cost2 = Math.sqrt(cost2)
		 c_nol.push([1, t-1, cost1])
		 c_nol.push([t, h, cost2])
		 if mincost[h-1][1] > cost1+cost2
			 mincost[h-1][0] = t
			 mincost[h-1][1] = cost1+cost2
		 end
		 cost1 = 0
		 cost2 = 0
	 end
 end

 p "mincost"
 mincost.each do |i|
    p i
 end

#Put out arg_minC() to output file.
 mincost.each_with_index do |outer_array,i|
    outp.printf("%d,",mincost[i][0])
    outp.printf("%f,",mincost[i][1])
    outp.putc("\n")
 end
 
#Step3, Saerch arg_mine().
 #C() calculate and put in to c_nol. And c_nol convert and make c_nolarray for treating easier.
 c_nolarray = Array.new(end_s.length).map{Array.new(end_s.length)}
 
 p 'c_nol'
 c_nol.each do |i|
    p i
 end

 c_nol.sort!
 c_nol.each_with_index do |facter,i|
    for i in 0..(c_nol.length-1)
            if c_nol[i] == c_nol[i+1]
           	 c_nol.delete_at(i+1)
            end
    end
 end

 c_nol.each do |array|
    c_nolarray[array[0]-1][array[1]-1] = array[2]
 end

 p "c_nol"
 c_nol.each do |i|
    p i
 end

 p "c_nolarray"
 c_nolarray.each do |i|
    p i
    print "\n"
 end

#Saerch arg_mine().
 e = Array.new(end_s.length).map{Array.new(end_s.length).map{Array.new(2,1000)}}
 mincost3 = Array.new
 
 0.upto(e.length-1) do |i|
    e[i][1][0] = mincost[i][0]
    e[i][1][1] = mincost[i][1]
 end
 
 #e.each do |i|
 # p i
 #end
 #c_nolarray.each do |i|
 # p i 
 #end
 #mincost.each do |i|
 # p i
 #end

 3.upto(end_s.length) do |q|
    q.upto(end_s.length) do |h|
       q.upto(h) do |t|
#	  p e[t-2][q-2]
#	  p c_nolarray[t-1][h-1]
	  if e[t-1][q-1][1] > e[t-2][q-2][1]+c_nolarray[t-1][h-1]
	     e[t-1][q-1][0] = t
             e[t-1][q-1][1] = e[t-2][q-2][1]+c_nolarray[t-1][h-1]
	  end
       end
    end
 end

 e.each do |i|
    p i
    print "\n"
 end 

#Step4, separate segments.
 j = $stdin.gets.to_i
 g = end_s.length
 res = Array.new

 j.downto(2) do |i|
    res.push(e[g-1][i-1][0])
    g = e[g-1][i-1][0]-1
 end

 p res

inp.close
outp.close
