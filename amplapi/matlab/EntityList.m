classdef EntityList < EntityListBase

methods
    function result = subsref(self, key)
        switch key(1).type
             case '()'
                 if(length(key) < 2 && length(key.subs) == 1 && ischar(key.subs{1}))
                     entity = self.impl.find(key.subs{1});
                     if(isa(entity, 'com.ampl.Variable'))
                         result = Variable(entity);
                     elseif(isa(entity, 'com.ampl.Constraint'))
                         result = Constraint(entity);
                     elseif(isa(entity, 'com.ampl.Parameter'))
                         result = Parameter(entity);
                     elseif(isa(entity, 'com.ampl.Objective'))
                         result = Objective(entity);
                     elseif(isa(entity, 'com.ampl.Set'))
                         result = Set(entity);
                     else
                         result = entity;
                     end
                 else
                    error('Entity:subsref', 'Not a supported subscripted reference')
                 end
                 return
             case '.'
                 result = builtin('subsref',self,key);
                 return
             case '{}'
                  error('Entity:subsref', 'Not a supported subscripted reference')
        end
    end

    function obj = EntityList(impl)
        obj@EntityListBase(impl);
    end

    function disp(self)
        s = self.size();
        if s==1
            fprintf('This map contains %d entitiy\n', s);
        else
            fprintf('This map contains %d entitiies\n', s);
        end
    end

end
end
