classdef Tuple < TupleBase
    
    methods
        function obj = Tuple(varargin)
            
            if(size(varargin)>1)
                error('Use Tuple.join to combine arrays in a Tuple')
            end
            if size(varargin) > 0
                a =  com.ampl.Tuple(varargin);
            else
                a = com.ampl.Tuple();
            end
            obj@TupleBase(a)
        end
        
        
        function display(self)
            self.impl.toString()
        end
    end
end

