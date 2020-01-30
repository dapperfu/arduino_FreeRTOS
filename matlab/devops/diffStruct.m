function diffStruct(a,b)
% Compare 2 structures. Used to compare block parameters after making a
% change in the simulink GUI.
%
% Used most often to compare simulink blocks & masks when you make changes
% to them. Assists in doing things programatically.
%
% Examples:
% a=get(gcbh);
% % Make change in Simulink GUI.
% b=get(gcbh);
% diffStruct(a,b)

% Get all of the field names of a & b.
aFields=fieldnames(a);
bFields=fieldnames(b);
% If there are different number of fields, then it probably isn't from the
% same structure. Don't do a comparison.
if length(a)~=length(b)
    error('Make sure ''a'' and ''b'' are the same datatype. Different number of fields');
end
% Reshape all of the blocks.
aFields=reshape(aFields,1,numel(aFields));
% Loop through all of the fields.
for f=aFields
    field=f{1};
    % If the fields are the same. Don't do anything!
    try
        if isequal(a.(field),b.(field))
            continue;
        end
    catch
        continue
    end
    % If they are different print the field.
    fprintf('%s: ', field);
    % Depending on the class, print the value of a structure.
    switch class(a.(field))
        case 'char'
            fprintf('%s',a.(field));
        case 'double'
            if length(a.(field))==1
                fprintf('%f',a.(field));
            else
                fprintf('[');
                fprintf('%f,',a.(field));
                fprintf(']');
            end
        case 'cell'
            tmp=a.(field);
            for i=1:numel(tmp);
                switch class(tmp)
                    case 'char'
                        fprintf('%s',tmp);
                    case 'double'
                        if length(tmp)==1
                            fprintf('%f',tmp);
                        else
                            fprintf('[');
                            fprintf('%f,',tmp);
                            fprintf(']');
                        end
                    case {'cell','struct','Capabilities'}
                end
            end
        case 'logical'
            if a.(field)
                fprintf('true');
            else
                fprintf('false');
            end
        otherwise
            fprintf('[%s]',class(a.(field)))
    end
    % Print other structure with an arrow indicating the change.
    fprintf(' -> ');
    switch class(b.(field))
        case 'char'
            fprintf('%s',b.(field));
        case 'double'
            if length(b.(field))==1
                fprintf('%f',b.(field));
            else
                fprintf('[');
                fprintf('%f,',b.(field));
                fprintf(']');
            end
        case 'cell'
            tmp=b.(field);
            for i=1:numel(tmp);
                switch class(tmp)
                    case 'char'
                        fprintf('%s',tmp);
                    case 'double'
                        if length(tmp)==1
                            fprintf('%f',tmp);
                        else
                            fprintf('[');
                            fprintf('%f,',tmp);
                            fprintf(']');
                        end
                    case {'cell','struct','Capabilities'}
                end
            end
        case 'logical'
            if b.(field)
                fprintf('true');
            else
                fprintf('false');
            end
        otherwise
            fprintf('[%s]',class(b.(field)))
    end
    fprintf('\n');
end
fprintf('\n');
% Print instructions on how to programatically change the settings.
for f=aFields
    field=f{1};
    try
        if isequal(a.(field),b.(field))
            continue;
        end
        switch class(b.(field))
            case 'char'
                fprintf('set(gcb,''%s'',''%s'');\n',field,b.(field));
            case 'double'
                if length(b.(field))==1
                    fprintf('set(gcb,''%s'',%f',field,b.(field));
                else
                    fprintf('set(gcb,''%s'',[',field);
                    fprintf('%f,',b.(field));
                    fprintf('];\n');
                end
            case 'logical'
                if b.(field)
                    fprintf('set(gcb,''%s'',true);\n',field);
                else
                    fprintf('set(gcb,''%s'',false);\n',field);
                end
            otherwise
                % pass
        end
    catch
       % pass 
    end
end